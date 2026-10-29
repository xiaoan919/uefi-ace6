#!/usr/bin/env python3
"""Assemble a diagnostic boot image from BootShimProbe + the built UEFI FD.

Why this exists: the stock BootShim.S copies the FD to FD_BASE and jumps with
no output at all. On the first hardware attempt the phone came back to Android
with no pstore record of our code, so the failure is either "never executed"
or "executed and faulted before anything could log". BootShimProbe.S splits
that in two: it paints the cont_splash framebuffer white, waits, then calls
PSCI SYSTEM_RESET. The screen and the reboot itself become the signal.

Addresses come from this unit's own runtime device tree:
  fdt_dts/runtime_merged.dts:721  splash_region
    reg = <0x00 0xfc800000 0x00 0x2b00000>
which is the same extent ace6Pkg already declares as Display_Reserved.
"""
import argparse
import gzip
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent
MKBOOTIMG = REPO / "Resources" / "Scripts" / "mkbootimg.py"
SHIM_DIR = REPO / "BootShim"

FB_BASE = 0xFC800000
FB_FILL = 0x100000   # 1 MiB, well inside the 43 MiB splash region


def run(cmd, cwd=None):
    print("  $ " + " ".join(str(c) for c in cmd))
    r = subprocess.run([str(c) for c in cmd], cwd=cwd)
    if r.returncode != 0:
        print(f"  FAILED (exit {r.returncode})")
        return False
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fd", required=True, help="path to SILICIUM_UEFI.fd")
    ap.add_argument("--dtb", required=True, help="device tree to append")
    ap.add_argument("--out", required=True, help="output boot image")
    ap.add_argument("--reset", type=int, default=1,
                    help="1 = paint then reboot, 0 = paint then enter the FD")
    ap.add_argument("--delay", type=int, default=10,
                    help="seconds to hold the marker before reset")
    ap.add_argument("--fd-base", default="0xa7100000")
    ap.add_argument("--fd-size", default="0x300000")
    args = ap.parse_args()

    fd = Path(args.fd)
    dtb = Path(args.dtb)
    for p in (fd, dtb, MKBOOTIMG):
        if not p.is_file():
            print(f"  MISSING {p}")
            return 1

    defs = " ".join([
        f"-DFB_BASE={FB_BASE:#x}",
        f"-DFB_FILL={FB_FILL:#x}",
        f"-DPROBE_RESET={args.reset}",
        f"-DPROBE_DELAY_S={args.delay}",
    ])

    if not run(["make", "-B", "SHIM_SRC=BootShimProbe.S",
                "REQUIRES_KERNEL_HEADER=1",
                f"FD_BASE={args.fd_base}", f"FD_SIZE={args.fd_size}",
                f"EXTRA_DEFS={defs}"], cwd=SHIM_DIR):
        return 1

    shim = SHIM_DIR / "BootShim.bin"
    payload = shim.read_bytes() + fd.read_bytes()
    kernel_gz = gzip.compress(payload, 9)
    kernel = kernel_gz + dtb.read_bytes()
    print(f"  shim {shim.stat().st_size} B + fd {fd.stat().st_size} B")
    print(f"  kernel {len(kernel_gz)} B gz + dtb {dtb.stat().st_size} B")

    tmp = Path(args.out).with_suffix(".kernel.bin")
    tmp.write_bytes(kernel)
    try:
        ok = run([sys.executable, MKBOOTIMG,
                  "--kernel", tmp,
                  "--header_version", "4",
                  "-o", args.out])
    finally:
        tmp.unlink(missing_ok=True)

    if ok:
        out = Path(args.out)
        print(f"  output {out} ({out.stat().st_size} B)")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())

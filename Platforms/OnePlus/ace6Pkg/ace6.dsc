##
#
#  Copyright (c) 2011 - 2022, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2020, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = ace6
  PLATFORM_GUID                  = E6ADAA2E-BB93-448C-806C-06F0F7B2D44D
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/ace6Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = RELEASE|DEBUG
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = ace6Pkg/ace6.fdf
  USE_CUSTOM_DISPLAY_DRIVER      = 0

  #
  # 0 = Mu drivers only. The previous stage's display keeps scanning out, so the
  #     boot manager is visible without any vendor hardware driver.
  # 1 = also load the stock vendor drivers (SMEM, clocks, RPMH, UFS, USB, ...).
  #
  # The on-unit log shows the vendor EnvDxeEnhanced.efi loading and then
  # ASSERTing in SerialDxe.c:849 with RETURN_ERROR, which stops the boot before
  # the menu. sheng defaults this to 0 for the same reason.
  #
  ACE6_VENDOR_HW                 = 0

  #
  # 1 = include SmbiosDxe and SmBiosTableDxe.
  # SmbiosDxe asserts on the unit before it publishes its protocol, and the
  # loader does not need SMBIOS, so it stays off until the boot chain works.
  #
  ACE6_SMBIOS                    = 0

  #
  # 0 = SM8750-AB
  # 1 = SM8750-3-AB
  # 2 = SM8750-AC
  #
  SOC_TYPE                       = 0

!include PakalaPkg/PakalaPkg.dsc.inc

[PcdsFixedAtBuild]
  #
  # DDR Memory
  #
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000

  #
  # UEFI Stack
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0xA760D000
  gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x40000

  #
  # SMBIOS
  #
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemManufacturer|"OnePlus"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Ace 6"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"PLQ110"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"PLQ110"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemBoardModel|"24851"

  #
  # Simple Frame Buffer
  #
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferWidth|1272
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferHeight|2800
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferColorDepth|32

  #
  # Boot Manager
  #
  # The default timeout is a few seconds, which is too short to read the screen
  # on the first bring-up: the panel shows the Project Silicium banner and the
  # menu frame, then the platform resets before anything can be inspected or a
  # key can be pressed. 60 s keeps the front page up long enough to photograph
  # and to navigate with the volume keys.
  #
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|60

  #
  # Platform PEI
  #
  gQcomPkgTokenSpaceGuid.PcdPlatformType|"LA"

[LibraryClasses]
  #
  # Memory Libraries
  #
  MemoryMapLib|ace6Pkg/Library/MemoryMapLib/MemoryMapLib.inf

  #
  # QCOM Libraries
  #
  ConfigurationMapLib|ace6Pkg/Library/ConfigurationMapLib/ConfigurationMapLib.inf

  #
  # UniXNU loader libraries
  #
  # The loader reads the payload through the FDT handoff, so it needs the HOB
  # with the FDT address and the FDT parser itself.
  #
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  FdtLib|MdePkg/Library/BaseFdtLib/BaseFdtLib.inf
  UniXNULib|UniXNUPkg/Library/UniXNULib/UniXNULib.inf

[Components]
  #
  # ACPI Tables
  #
  #pagani/AcpiTables.inf

  #
  # UniXNU loader
  #
  # Without these the platform reaches the DXE core, publishes the panel and
  # then has nothing to boot: no menu, no payload volume, no kernel handoff.
  # The list is the one docs/porting/uefi-firmware.md names as mandatory.
  #
  UniXNUPkg/Application/UniXNU/UniXNU.inf
  UniXNUPkg/Driver/UniXNUDxe/UniXNUDxe.inf
  UniXNUPkg/Driver/UniXNURamDiskDxe/UniXNURamDiskDxe.inf
  DarwinBootPkg/Driver/DarwinBoot.inf

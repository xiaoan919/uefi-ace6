  INF MdeModulePkg/Core/Dxe/DxeMain.inf
  INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/EnvDxe/EnvDxeEnhanced.inf
!endif

  INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf
  INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
  INF Binaries/pagani/QcomPkg/Drivers/TzDxe/ScmDxeCompat.inf
  INF Binaries/pagani/QcomPkg/Drivers/TzDxe/TzDxeLA.inf
!endif

  INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf
  INF EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
  INF MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
  INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
  INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  INF ArmPkg/Drivers/ArmGicDxe/ArmGicDxe.inf
  INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf

#
# The vendor block. Every one of these comes from Binaries/pagani, which is the
# prebuilt driver set of the OnePlus 13s, and all of them are gated because the
# unit showed that leaving them in stops the boot before the menu:
#
#   EnvDxeEnhanced  ASSERT SerialDxe.c:849 (Status = Not Found)
#   XhciDxe         ASSERT Autogen.c:284 (Status = Not Found)
#
# They are a graph: XhciDxe needs the PCI emulation layer, which needs the
# vendor DWС3 and clock stack, which needs RPMh and SMEM. Turning off one leaf
# only moves the failure to its neighbour, so the whole set goes together and
# comes back together once the missing device path is understood.
#
!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/HWIODxe/HWIODxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/I2CDxe/I2CDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/QupDxe/QupDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf
!endif

  INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf

#
# The loader chain. ReportStatusCode and DevicePath stay outside the gate: the
# first is what turns a driver failure into something on the panel, the second
# is what every console and file-system driver needs to describe itself.
#
  INF UniXNUPkg/Driver/UniXNURamDiskDxe/UniXNURamDiskDxe.inf
  INF DarwinBootPkg/Driver/DarwinBoot.inf

  INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  INF FatPkg/EnhancedFatDxe/Fat.inf
  INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/UFSDxe/UFSDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/NpaDxe/NpaDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/ULogDxe/ULogDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/MailboxDxe/MailboxDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/QcomScmiDxe/QcomScmiDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/VcsDxe/VcsDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/ClockDxe/ClockDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/ICBDxe/ICBDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/SmemDxe/SmemDxe.inf
!endif

  INF MdeModulePkg/Universal/BdsDxe/BdsDxe.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/RscDxe/RscDxe.inf
!endif

  INF EmbeddedPkg/SimpleTextInOutSerial/SimpleTextInOutSerial.inf
  INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
  INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/CPRDxe/CPRDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/SPIDxe/SPIDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/SdccDxe/SdccDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf
!endif

#
# Display. USE_CUSTOM_DISPLAY_DRIVER = 1 loads the stock vendor DisplayDxe with
# the panel data in RAW.inc; otherwise SimpleFbDxe publishes a GOP on the frame
# buffer the previous stage left scanning out. The latter is what sheng uses by
# default and what we need while the vendor stack is off.
#
!if $(USE_CUSTOM_DISPLAY_DRIVER) == 1
!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
!endif
!else
  INF SiliciumPkg/Drivers/SimpleFbDxe/SimpleFbDxe.inf
!endif

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/OcdtDxe/OplusProject.inf
  INF Binaries/pagani/QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
  INF Binaries/pagani/QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/TsensDxe/TsensDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/XhciDxe/XhciDxe.inf
!endif

  INF MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf

!if $(ACE6_VENDOR_HW) == 1
  INF Binaries/pagani/QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/UCDxe/UCDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/RNGDxe/RngDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/PILDxe/PILDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
  INF Binaries/pagani/QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
!endif

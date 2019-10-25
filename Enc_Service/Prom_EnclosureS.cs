﻿using System;
using System.ServiceProcess;
using System.IO;
using System.Management;
using System.Diagnostics;
using Enclsoure;
using Microsoft.Win32;
using System.Collections.Generic;
using System.Timers;
using System.Threading;

namespace Prom_Enclosure_Serives
{
    public partial class Prom_EnclosureS : ServiceBase
    {
        private System.Timers.Timer MyTimer;
        public Enclsoure_class Enclosure;
        public Dictionary<string, uint?[]> AllData;
        public uint?[] GetRegFan;// GetRegFan.Length = 4 * Fan.Length
        public uint?[] GetRegTemperature;// GetRegTemperature.Length = 4 * Temperature.Length
        public uint?[] GetRegVoltage;// GetRegVoltage.Length = 4 * Voltage.Length
        public uint?[,] GetRegLed;

        public uint?[] Temp_threshold;
        public static bool process_flag = false;

        public static string TimeParameter = "30";

        public Prom_EnclosureS()
        {
            Program.Pro_Event_viewer.WriteEntry("hello in there");
            InitializeComponent();

            DirectoryInfo LogExist = new DirectoryInfo(Log_File.LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(Log_File.LogName + "*");
            Log_File.LogId = (FileExist.Length - 1);
            for (int i = 0; i <= Log_File.LogId; i++)
            {
                Log_File.LogFile[i] = Convert.ToString(FileExist[i]);
            }

            if (!EventLog.SourceExists("Promise"))
            {
                EventLog.CreateEventSource("Promise", "Promise_event");
            }
            
            this.Enclosure = new Enclsoure_class();
        }

        protected override void OnStart(string[] args)
        {

            Program.Pro_Event_viewer.WriteEntry("Enc_Service started...");
            Program.Pro_Event_viewer.WriteEntry("TimeParameter= \"" + TimeParameter + "\"\n");
            Log_File.FileLog("Service is Start!JOEL");
            Enc_Service = new Prom_EnclosureS();

            WqlEventQuery query = new WqlEventQuery(@"SELECT * FROM RegistryKeyChangeEvent WHERE Hive='HKEY_LOCAL_MACHINE' AND KeyPath='SOFTWARE\\Pro_HWMonitor'");
            ManagementEventWatcher Registry_Watcher = new ManagementEventWatcher(query);
            Registry_Watcher.EventArrived += new EventArrivedEventHandler(Enc_Service.ChkReqRoutine);

  
            
            try
            {
                Registry_Watcher.Start();
                MyTimer = new System.Timers.Timer();
                MyTimer.Interval = Convert.ToInt32(TimeParameter) * 1000;
                MyTimer.Elapsed += new ElapsedEventHandler(MyTimer_Elapsed);
                MyTimer.Start();
            }
            catch (Exception e)
            {
                Log_File.FileLog(Convert.ToString(e));
            }
        }

        protected override void OnStop()
        {
            Log_File.FileLog("Service is Stop!");
            try
            {
                Program.Pro_Event_viewer.WriteEntry("Enc_Service stopped...");
            }
            catch (Exception e)
            {
                Program.Pro_Event_viewer.WriteEntry("Stop Management Event Watcher failed...");
                Program.Pro_Event_viewer.WriteEntry(Convert.ToString(e));
            }
        }

        private void MyTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            //enc_Service = new Enc_Service();
            Enc_Main();

            //Log Test Code
            for (int i = 0; i < 50; i++)
            {
                //FileLog("Log Test");
            }
        }

        public void Close()
        {
            Console.WriteLine("Computer has already been displosed.");
        }

        public Prom_EnclosureS Enc_Service;
        public  void Enc_Main()
        {
            int interval = -1; // This value will not be changed if no "-i" in args.

            if (interval >= 0)
            {
                // Exit if this application is already running in another process.
                Process curProcess = Process.GetCurrentProcess();
                var procs = Process.GetProcesses();
                foreach (var proc in procs)
                {
                    if (proc.Id != curProcess.Id && proc.ProcessName == curProcess.ProcessName)
                    {
                        Console.WriteLine("This application is already running as process {0}", proc.Id);
                        OnStop();
                    }
                }
            }
                    Console.WriteLine("----------------------------v0.1");
                    Enc_Service.Enclosure.GetEnclosureData(ref AllData);
                    Enc_Service.SetToREG();
            process_flag = true;
        }



        private static UInt32 VoltageToU32(byte voltage)
        {
            UInt32 high = (UInt32)(voltage >> 4);
            UInt32 low = (UInt32)(voltage & 0x0F);
            return ((high << 16) | low);
        }

        private void SetToREG()
        {
            try
            {
                RegistryKey localKey = null, softwareKey = null, key4Driver = null;

                try
                {
                    // RegistryKey for FW
                    localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                    softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                    key4Driver = softwareKey.CreateSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);
                    if (key4Driver == null)
                        throw new Exception("Unable to create or open registry key");
                    Update(key4Driver);
                }
                finally
                {
                    if (key4Driver != null) key4Driver.Close();
                    if (softwareKey != null) softwareKey.Close();
                    if (localKey != null) localKey.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());

            }
        }

        //public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        public void ChkReqRoutine(object sender, EventArrivedEventArgs e)
        {
            bool request_flag = false;

            if (GetRegistry("FanConfig"))
            {
                Enclosure.Enclosure_SET_fan(GetRegFan);
                request_flag = true;
            }
            if (GetRegistry("LedConfig"))
            {
                Enclosure.Enclosure_SET_led(GetRegLed);
                request_flag = true;
            }
            if (GetRegistry("Temp_threshold"))
            {
                Enclosure.Enclosure_SET_Temp_threshold(Temp_threshold);
                request_flag = true;
            }
            //return request_flag;
        }

        private bool GetRegistry(string unit)
        {

            byte[] RegValue = null;

            RegValue = null;
            switch (unit)
            {
                case "FanConfig":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        return false;
                    }
                    else
                    {
                        GetRegFan = new uint?[RegValue.Length / 4];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int FanLevel = RegValue[i + 2];
                                int FanCount = RegValue[i];
                                int FanSpeed = (FanLevel << 16) + FanCount;
                                //Console.WriteLine("FanLevel = {01:x}  FanCount = {1:x} ", FanLevel, FanCount);
                                GetRegFan[i / 4] = Convert.ToUInt32(FanLevel);
                                //Console.WriteLine("FanLevel[{0}] = {1:x} ", (i / 4), GetRegFan[i / 4]);
                            }
                        }
                    }
                    break;
                case "Temperature":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        Console.WriteLine("The unit {0} should not to change !", unit);
                        return false;
                    }
                    else
                    {
                        GetRegTemperature = new uint?[RegValue.Length];
                        Console.WriteLine("RegValue.Length={0}", RegValue.Length);
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                GetRegTemperature[i] = Convert.ToUInt32(RegValue[i]);
                                Console.WriteLine("TemperatureReg[{0}] = {1:x} ", (i / 4), GetRegTemperature[i]);
                            }
                        }
                    }
                    break;
                case "Voltage":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        Console.WriteLine("The unit {0} should not to change !", unit);
                        return false;
                    }
                    else
                    {
                        GetRegVoltage = new uint?[RegValue.Length];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int volreg = ((RegValue[i + 2] << 4) | (RegValue[i]));
                                GetRegVoltage[(i / 4)] = Convert.ToUInt32(volreg);
                                Console.WriteLine("VoltageReg[{0}] = {1:x} ", (i / 4), volreg);
                            }
                        }
                    }
                    break;
                case "Temp_threshold":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        return false;
                    }
                    else
                    {
                        Temp_threshold = new uint?[RegValue.Length / 4];
                        for (int i = 0; i < RegValue.Length; i++)
                        {
                            if (i % 4 == 0)
                            {
                                int Temp = RegValue[i + 2];
                                Console.WriteLine("Temp_threshold = {0:x}  ", Temp);
                                Temp_threshold[i / 4] = Convert.ToUInt32(Temp);
                            }
                        }
                    }
                    break;

                case "LedConfig":
                    if (!GetRegValue(unit, ref RegValue))
                    {
                        return false;
                    }
                    else
                    {
                        GetRegLed = new uint?[RegValue.Length / 4, 2];
                        for (int i = 0; i < RegValue.Length; i += 4)
                        {
                            if (i % 4 == 0)
                            {
                                int ledreg = ((RegValue[i + 2]) | (RegValue[i] << 8));
                                GetRegLed[(i / 4), 0] = (uint)(i / 4);
                                GetRegLed[(i / 4), 1] = Convert.ToUInt32(ledreg);
                                Console.WriteLine("i = [{0:x}]", i);
                                Console.WriteLine("LedReg = [{0:x}]", ledreg);
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
            return true;
        }

        private bool GetRegValue(string UnitName, ref byte[] RegValue)
        {
            try
            {
                RegistryKey localKey = null, softwareKey = null, key4Driver = null;

                localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64);
                softwareKey = localKey.OpenSubKey("SOFTWARE", true);
                key4Driver = softwareKey.OpenSubKey("Pro_HWMonitor", RegistryKeyPermissionCheck.ReadWriteSubTree);

                byte[] ValueUnit = (byte[])key4Driver.GetValue(UnitName);

                RegValue = new byte[(ValueUnit[0] & 0x3F) * 4];

                UInt32 FanFlag = (UInt32)(ValueUnit[0] & 0x80);
                if (FanFlag == 0)
                {
                    key4Driver.Close();
                    softwareKey.Close();
                    localKey.Close();
                    return false;
                }

                for (int i = 0; i < RegValue.Length; i++)
                {
                    RegValue[i] = ValueUnit[i + 4];
                }

                ValueUnit[0] = Convert.ToByte(Convert.ToInt16(ValueUnit[0]) & 0x7F);
                key4Driver.SetValue(UnitName, ValueUnit, RegistryValueKind.Binary);
                key4Driver.Close();
                softwareKey.Close();
                localKey.Close();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(" Cannot get reg {0},{1} ", UnitName, ex);
                return false;
            }
        }

        /**
         * Write the sensor data to registry
         */
        private void Update(RegistryKey key4Driver)
        {
            string[] subkeyNames = key4Driver.GetSubKeyNames();
            string[] valueNames = key4Driver.GetValueNames();

            foreach (KeyValuePair<string, uint?[]> kv in AllData)
            {
                using (MemoryStream buffer = new MemoryStream())
                {
                    using (BinaryWriter writer = new BinaryWriter(buffer))
                    {

                        switch (kv.Key)
                        {
                            case "Fan":
                                writer.Write((UInt32)kv.Value.Length);
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    writer.Write((UInt32)kv.Value[i]);
                                }

                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;
                            case "Control":
                                break;
                            case "Voltage":
                                writer.Write((UInt32)kv.Value.Length);
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    uint u32Voltage = VoltageToU32(Convert.ToByte(kv.Value[i]));
                                    writer.Write(u32Voltage);
                                }
                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;
                            case "Temperature":
                                writer.Write((UInt32)kv.Value.Length);
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    writer.Write((UInt32)kv.Value[i]);
                                }
                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;
                            case "Led":
                                writer.Write((UInt32)kv.Value.Length);
                                for (int i = 0; i < kv.Value.Length; i++)
                                {
                                    writer.Write((UInt32)kv.Value[i]);
                                }

                                key4Driver.SetValue(kv.Key, buffer.ToArray(), RegistryValueKind.Binary);
                                break;

                            default:
                                break;
                        }

                    }
                }
            }
        }
    }
}

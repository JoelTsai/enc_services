/*---------------------------------------------------------------------------**
**          Filename    : enclosure.cs                                       **
**          Description : enclosure functions                                **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/


using System;
using System.Threading;
using System.Globalization;
using System.Text;
//using OpenHardwareMonitor.Hardware;
using System.Collections;
using Chip.Contrl;
using platformwmi;
using System.Collections.Generic;
using OpenLibSys;
using WingRing;
using i2api;
using System.Timers;

namespace Enclsoure
{
    static class Enclsoure_Constants
    {

        internal const uint ENC_TEMP_INVALID_VALUE = 0x8000;
        internal const uint ENC_TEMP_STAT_NORMAL = 0x0000;
        internal const uint ENC_TEMP_STAT_OC = 0x0001;/* over critical */
        internal const uint ENC_TEMP_STAT_OW = 0x0002; /* over warning */
        internal const uint ENC_TEMP_STAT_UC = 0x0004;/* under critical */
        internal const uint ENC_TEMP_STAT_UW = 0x0008;/* under warning */

        internal const uint VOL_STS_NORMAL = 0x0;
        internal const uint VOL_STS_CRIT_OVER = 0x1;
        internal const uint VOL_STS_WARN_OVER = 0x2;
        internal const uint VOL_STS_CRIT_UNDER = 0x4;
        internal const uint VOL_STS_WARN_UNDER = 0x8000;

        internal const uint FAN_OPERATIONAL = 0;
        internal const uint FAN_MALFUNCTIONING = 1;
        internal const uint FAN_NOT_INSTALLED = 2;
        internal const uint FAN_STS_UNKNOWN = 0x80;

        internal const uint Temp_OW_threshold_default = 90;
        internal const uint Temp_OC_threshold_default = 100;
        internal const uint HDD_OW_threshold_default = 55;
        internal const uint HDD_OC_threshold_default = 65;
    }


    internal struct All_senserdata
    {
        public uint?[] all_voltages;
        public uint?[] all_temperatures;
        public uint?[] all_fans;
        public uint?[] all_leds;
        public uint?[] PSU_temperatures;
        public uint?[] PSU_fans;
    };

    internal struct TEMPOBJ
    {
        public uint?[] Temp_OC_threshold;
        public uint?[] Temp_OW_threshold;
        public uint?[] prev_temp;
        public uint?[] hys_temp;

        public uint?[] prev_stat;
        public uint?[] cur_stat;
        internal DateTime[] Controller_OC_time;

        public TEMPOBJ(int Length)
        {
            Temp_OC_threshold=new uint?[Length];
            Temp_OW_threshold = new uint?[Length];
            hys_temp = new uint?[Length];
            prev_temp = new uint?[Length];
            cur_stat = new uint?[Length];
            prev_stat = new uint?[Length];
            Controller_OC_time = new DateTime[Length];
            for (int i = 0; i < Length; i++)
            {
                prev_temp[i] = Enclsoure_Constants.ENC_TEMP_INVALID_VALUE;
                cur_stat[i] = 0;
                prev_stat[i] = 0;
                Temp_OC_threshold[i] = Enclsoure_Constants.Temp_OC_threshold_default;
                Temp_OW_threshold[i] = Enclsoure_Constants.Temp_OW_threshold_default;
                Controller_OC_time[i] = DateTime.Now;
                hys_temp[i] = 4;
            }
        }
    };

    internal struct HDD_TEMPOBJ
    {
        public uint?[] HDD_OC_threshold;
        public uint?[] HDD_OW_threshold;
        public uint?[] cur_temp;
        public uint?[] prev_temp;
        public uint?[] hys_temp;

        public uint?[] prev_stat;
        public uint?[] cur_stat;
        internal DateTime[] PD_OC_time;

        public HDD_TEMPOBJ(uint Length)
        {
            HDD_OC_threshold = new uint?[Length];
            HDD_OW_threshold = new uint?[Length];
            hys_temp = new uint?[Length];
            cur_temp = new uint?[Length];
            prev_temp = new uint?[Length];
            cur_stat = new uint?[Length];
            prev_stat = new uint?[Length];
            PD_OC_time = new DateTime[Length];
            for (int i = 0; i < Length; i++)
            {
                prev_temp[i] = 0xFF;
                cur_temp[i] = 0xFF;
                prev_stat[i] = 0;
                cur_stat[i] = 0;
                HDD_OC_threshold[i] = Enclsoure_Constants.HDD_OC_threshold_default;
                HDD_OW_threshold[i] = Enclsoure_Constants.HDD_OW_threshold_default;
                PD_OC_time[i] = DateTime.Now;
                hys_temp[i] = 4;
            }
        }


    };
    /*static class Constants
    {

        public const uint test = 0x00;

    }*/

    public class Enclsoure_class
    {
        public static OpenLibSys.Ols testold = null;

        private Dictionary<string, uint?[]> sensorData;

        public NCT677X NCT;
        public NCT7802 NCT7802_BP;
        public PSU PSU;
        // public CPU CPU;
        public TCA6416 tca6416;
        All_senserdata outdata;
        TEMPOBJ TempObj, PSU_tempObj;
        HDD_TEMPOBJ HDD_temp;

        private static readonly uint FAN_Default_LEVEL = 0x2;
        private static uint FAN_LEVEL = FAN_Default_LEVEL;//init will set this level to fan

        //private static readonly uint FAN_offset = 0x03;//this offset is the level different of SYS_FAN and CPU_FAN
        //public uint Temp_OC_threshold = 100;
        // public uint Temp_OW_threshold = 80;
        public const ushort Series_VA8200 = 0x09A0;
        public const ushort Model_VA8200 = 0x09A0;
        public const ushort Model_VA8200D = 0x9B0;
        public const ushort Model_VA8100 = 0x09A1;
        public const ushort Model_VA8020 = 0x09A2;

        public  static ushort Model_ID = 0;



        private uint?[] NCT_voltages = new uint?[0];
        private uint?[] NCT_temperatures = new uint?[0];
        private uint?[,] NCT_fans = new uint?[0,0];
        private uint?[,] SMB_fans = new uint?[0,0];
        private uint?[] TCA_leds = new uint?[0];
        private uint?[] CPU_temperatures = new uint?[0];
        private uint?[] PSU_temperatures = new uint?[0];
        private uint?[,] PSU_fans = new uint?[0, 0];

        private uint FAN_MASK_CPU = 0x0100;
        private uint FAN_MASK_SYS = 0x0200;

        private const uint FAN_Invalid = 0x0000;
        private const uint FAN_Decrease = 0x0001;
        private const uint FAN_Increase = 0x0002;
        private const uint FAN_Max = 0x0004;

        public static uint Temp_OW_threshold = Enclsoure_Constants.Temp_OW_threshold_default;
        public static uint Temp_OC_threshold = Enclsoure_Constants.Temp_OC_threshold_default;
        public static uint HDD_OW_threshold = Enclsoure_Constants.HDD_OW_threshold_default;
        public static uint HDD_OC_threshold = Enclsoure_Constants.HDD_OC_threshold_default;


        internal static ushort Fan_error = 0;
        private uint Fan_control_flag = 0;
        public static  uint Fan_color = TCA6416_Constants.ENC_LED_GREEN;
        public static uint GlobeError_color = TCA6416_Constants.ENC_LED_GREEN;
        internal static bool FAN_LED_trigger = false;
        internal static bool GlobeError_LED_trigger = false;
        internal static bool Blink_trigger = false; 
        internal static uint NET_LED = 0;
        internal static uint OPAS_LED = 0;

        static DateTime FAN_CHANGE_Time_offset;
        private TimeSpan FAN_CHANGE_time_diff;


        public static byte[,] Locatemask=new byte[2,2];
        public static bool HDD_OC_blink = false;
        public Thread PD_OC_blink_thread;
        public void Program()
        {
            PCHSMBUS.PCHSMBUS_init();
            NCT = new NCT677X();
           // CPU = new CPU();
            sensorData = new Dictionary<string, uint?[]>();
            if (Model_ID != 0xffff)
            {
                FAN_CHANGE_Time_offset = DateTime.Now.AddTicks(-3000000000);

                if (Model_ID != Model_VA8020)
                {
                    NCT7802_BP = new NCT7802();
                    NCT7802_BP.Chip_init(NCT7802_Constants.NCT7802Y_BP_HW_MONITOR_ADDR);
                    if (Model_ID == Model_VA8200D)//TBD how to detect model with daul power?
                    {
                        PSU = new PSU();
                    }
                }
                //CPU = new CPU();
                tca6416 = new TCA6416();

                FanInit();
                for (int i = 0; i < Locatemask.Length / Locatemask.Rank; i++)
                {
                    for (int j = 0; j < Locatemask.Rank; j++)
                    {
                        Locatemask[i,j] = 0;
                    }
                }
            }

        }

        private void Init_array(uint?[] target)
        {
            for (int i = 0; i < target.Length; i++)
                target[i] = 0x00;

        }
        public void FanInit()
        {
            NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_ALL, FAN_LEVEL);
            if (Model_ID != Model_VA8020)
            {
                NCT7802_BP.Nct7802y_set_fan_speed(NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL, FAN_LEVEL);
            }
        }


        public Enclsoure_class()
        {
            Program();
           // Init();  //it will already init in Ring0.cs
            NCT_voltages = new uint?[4];
            NCT_temperatures = new uint?[NCT677X.SIO_TEM_NUM];
            CPU_temperatures = new uint?[1];
            TCA_leds = new uint?[2];
            
            NCT_fans = new uint?[NCT677X.SIO_FAN_NUM,2];
            if (Model_ID != Model_VA8020 && Model_ID != 0xFFFF) 
            {
                SMB_fans = new uint?[2,2];
            }
            PSU_temperatures = new uint?[PSU_Constants.PSU_NUM];
            PSU_fans = new uint?[PSU_Constants.PSU_NUM, 2];

            outdata.all_fans = new uint?[(NCT_fans.Length+SMB_fans.Length)/2];
            outdata.all_voltages = new uint?[NCT_voltages.Length];
            outdata.all_temperatures = new uint?[NCT_temperatures.Length + CPU_temperatures.Length];
            outdata.all_leds = new uint?[TCA_leds.Length];
            outdata.PSU_temperatures = new uint?[PSU_Constants.PSU_NUM];
            outdata.PSU_fans = new uint?[PSU_Constants.PSU_NUM];


            TempObj = new TEMPOBJ(outdata.all_temperatures.Length);
            HDD_temp = new HDD_TEMPOBJ(I2connection.NumOfHDSlots);
            PSU_tempObj = new TEMPOBJ(Convert.ToInt32(PSU_Constants.PSU_NUM));
            Console.WriteLine("!!NumOfHDSlots = 0x{0:x} ", I2connection.NumOfHDSlots);
            PD_OC_blink_thread = new Thread(PD_OC_Blink);
        }

        public void GetEnclosureData(ref Dictionary<string, uint?[]> Outdata)
        //public void Test()
        {
            
            Enclosure_GET_fan();
            Enclosure_GET_volate();
            Enclosure_GET_temperatures();

            if (Model_ID != 0xffff)
            {
                Enclosure_GET_led();
                Fan_LED_control();
                VerifyPDtemp();
                /*if only use equal mark and after clear the target will also clear.*/

                Thermal_Management();
                if (HDD_OC_blink && !(Blink_trigger))
                {
                    Prom_Enclosure_Serives.Log_File.FileLog("HDD_OC_blink detect");
                    Console.WriteLine("!!HDD_OC_blink true");
                    if ((PD_OC_blink_thread.ThreadState == ThreadState.Unstarted))
                    {
                        Console.WriteLine("!!PD_OC_blink_thread.ThreadState={0}", PD_OC_blink_thread.ThreadState);
                        PD_OC_blink_thread.Start();
                    }
                    if((PD_OC_blink_thread.ThreadState == ThreadState.Stopped))
                    {
                        Console.WriteLine("PD_OC_blink_thread.ThreadState={0}", PD_OC_blink_thread.ThreadState);
                        PD_OC_blink_thread=new Thread(PD_OC_Blink);
                        PD_OC_blink_thread.Start();
                    }
                }


                for (int i = 0; i < outdata.all_temperatures.Length; i++)
                {
                    outdata.all_temperatures[i] = (TempObj.cur_stat[i] << 24) | outdata.all_temperatures[i];
                }
                sensorData.Add("Led", outdata.all_leds);


            }
            sensorData.Add("Temperature", outdata.all_temperatures);
            sensorData.Add("Fan", outdata.all_fans);
            sensorData.Add("Voltage", outdata.all_voltages);
            sensorData.Add("PSU_Temperature", outdata.PSU_temperatures);
            sensorData.Add("PSU_Fan", outdata.PSU_fans);
            //sensorData.Add("Led", outdata.all_leds);
            //

            Outdata = new Dictionary<string, uint?[]>(sensorData); 
            sensorData.Clear();

        }

        private void Enclosure_GET_fan()
        {
            int NTC_array_length = NCT_fans.Length / NCT_fans.Rank;
            int SMB_array_length = SMB_fans.Length / SMB_fans.Rank;
            int PSU_array_length = PSU_fans.Length / PSU_fans.Rank;
            NCT.Get_Fan(ref NCT_fans);

            //Array.Copy(NCT_fans, outdata.all_fans, NCT_fans.Length);
            for (int i = 0; i < NTC_array_length; i++)
            {
               // Console.WriteLine(" NCT_fans[{1}, 1] = 0x{0:x} ", NCT_fans[i, 1], i);
               // Console.WriteLine(" NCT_fans[{1}, 0] = 0x{0:x} ", NCT_fans[i, 0], i);
                outdata.all_fans[i] = (NCT_fans[i, 1] << 24) | NCT_fans[i, 0];
            }
            if (Model_ID != Model_VA8020 && Model_ID != 0xFFFF)
            {
                NCT7802_BP.Nct7802y_get_fan_speed(0x01, ref SMB_fans);
                NCT7802_BP.Nct7802y_get_fan_speed(0x02, ref SMB_fans);
                // Array.Copy(SMB_fans, 0, outdata.all_fans, NCT_fans.Length, SMB_fans.Length);
                for (int i = NTC_array_length; i < SMB_array_length + NTC_array_length; i++)
                {
                  //  Console.WriteLine(" SMB_fans[{1}, 1] = 0x{0:x} ", SMB_fans[i - NTC_array_length, 1], i);
                  //  Console.WriteLine(" SMB_fans[{1}, 0] = 0x{0:x} ", SMB_fans[i - NTC_array_length, 0], i);
                    outdata.all_fans[i] = (SMB_fans[i - NTC_array_length, 1] << 24) | SMB_fans[i - NTC_array_length, 0];
                }
            }
            PSU.GetPSUFanSpeed(ref PSU_fans);
            for (int i = 0; i < PSU_array_length; i++)
            {
                // Console.WriteLine(" NCT_fans[{1}, 1] = 0x{0:x} ", NCT_fans[i, 1], i);
                // Console.WriteLine(" NCT_fans[{1}, 0] = 0x{0:x} ", NCT_fans[i, 0], i);
                outdata.PSU_fans[i] = (PSU_fans[i, 1] << 24) | PSU_fans[i, 0];
            }

            //sensorData.Add("Fan", outdata.all_fans);


        }
        private void Enclosure_GET_volate()
        {
            NCT.Get_Voltage(ref NCT_voltages);
            Array.Copy(NCT_voltages, outdata.all_voltages, NCT_voltages.Length);
            //sensorData.Add("Voltage", outdata.all_voltages);

        }
        private void Enclosure_GET_temperatures()
        {
            /*NCT.Get_Temperature(ref NCT_temperatures);
            Array.Copy(NCT_temperatures, outdata.all_temperatures, NCT_temperatures.Length);

            CPU.GetCPUTEMP(ref CPU_temperatures);
            Array.Copy(CPU_temperatures, 0, outdata.all_temperatures, NCT_temperatures.Length, CPU_temperatures.Length);*/

            //sensorData.Add("Temperature", outdata.all_temperatures);

            NCT.Get_LPCIO_CPU_Temperature(ref CPU_temperatures);
          //  CPU.GetCPUTEMP(ref CPU_temperatures);
            Array.Copy(CPU_temperatures, outdata.all_temperatures, CPU_temperatures.Length);

            NCT.Get_Temperature(ref NCT_temperatures);
            Array.Copy(NCT_temperatures, 0, outdata.all_temperatures, CPU_temperatures.Length, NCT_temperatures.Length);

            PSU.Get_Temperature(ref PSU_temperatures);
            Array.Copy(PSU_temperatures, outdata.PSU_temperatures, PSU_temperatures.Length);
            /* for(int i=0;i<PSU_temperatures.Length;i++)
             {

                 Console.WriteLine("<<<<<<PSU {0} temp={1}", i, PSU_temperatures[i]);
             }
             Console.ReadLine();*/
        }

        public void Thermal_Management()
        {
           /* uint  a= 0xFF;
            Console.WriteLine("Joel :0x{0:x}.\n", a);
            a = ~(Enclsoure_Constants.ENC_TEMP_STAT_OC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_OW |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UW);
            Console.WriteLine("Joel :0x{0:x}.\n", a);*/


            Console.WriteLine("Into Thermal_Management");
            CheckTEMPstatus();
            ProcessTemperatureSts();

            //HDD
            CheckPDTEMPstatus();
            ProcessPDTemperatureSts();

            //PSU
            CheckPSUTEMPstatus();


            FAN_CHANGE_time_diff = DateTime.Now - FAN_CHANGE_Time_offset;
            if ((Fan_control_flag & FAN_Max) == FAN_Max)
            {
                AUTO_FAN(FAN_Max);
                FAN_CHANGE_Time_offset = DateTime.Now;
            }
            else if (((Fan_control_flag&FAN_Increase)==FAN_Increase)&& (FAN_CHANGE_time_diff.Ticks/10)> (180* 1000000))//&& now-timer>180
            {
                AUTO_FAN(FAN_Increase);
                FAN_CHANGE_Time_offset = DateTime.Now;
            }
            else if (((Fan_control_flag&FAN_Decrease)==FAN_Decrease)&& (FAN_CHANGE_time_diff.Ticks/10) > (300 * 1000000))//&& now-timer>300
            {
                AUTO_FAN(FAN_Decrease);
                FAN_CHANGE_Time_offset = DateTime.Now;
            }
            Console.WriteLine("FAN_LEVEL=0x{0:x}", FAN_LEVEL);
            Fan_control_flag = FAN_Invalid;
            UpdatePrevTempObjStat();
        }

        ///////////////////////////////
        ///controller thermal handle///
        ///////////////////////////////
        #region Controller thermal    

        #region Check Controller temp status 
        public void CheckTEMPstatus()
        {
            for(int i=0; i< outdata.all_temperatures.Length;i++)
            {

                //Console.WriteLine("outdata.all_temperatures[{0}] = {1} ", i, outdata.all_temperatures[i]);
                // Console.WriteLine(" NOW  Temp_OW_threshold[{0}] : 0x{1}", i, TempObj.Temp_OW_threshold[i]);
                // Console.WriteLine(" NOW  Temp_OC_threshold[{0}] : 0x{1}", i, TempObj.Temp_OC_threshold[i]);
                /*with out previous status*/
                if (TempObj.prev_temp[i]==Enclsoure_Constants.ENC_TEMP_INVALID_VALUE)
                {
                    if(outdata.all_temperatures[i] >= TempObj.Temp_OC_threshold[i])
                    {
                        TempObj.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_OW);
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                              I2connection_Events.EVT_CODE_TEMP_ABOVE_CRITICAL,
                                              Convert.ToUInt32(i));
                    }
                    else if (outdata.all_temperatures[i] >= TempObj.Temp_OW_threshold[i])
                    {
                        TempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                              I2connection_Events.EVT_CODE_TEMP_ABOVE_WARNING,
                                              Convert.ToUInt32(i));
                    }
                    else
                    {
                        TempObj.cur_stat[i] = 0;
                    }
                    continue;
                }
                if(!((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC)&&
                     (TempObj.prev_temp[i] >= TempObj.Temp_OC_threshold[i])&&
                     (outdata.all_temperatures[i] >= TempObj.Temp_OC_threshold[i]))
                {
                    /* Normal/Over warning  -> Over critical */
                    TempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear UC and UW */
                    TempObj.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OW | Enclsoure_Constants.ENC_TEMP_STAT_OC);
                    if ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) != Enclsoure_Constants.ENC_TEMP_STAT_OC)
                    {
                        Console.WriteLine("Joel : Normal/Over warning -> Over critical.\n");
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                             I2connection_Events.EVT_CODE_TEMP_ABOVE_CRITICAL,
                                             Convert.ToUInt32(i));
                        TempObj.Controller_OC_time[i] = DateTime.Now; ////update time base;
                    }
                }
           else if (!((TempObj.prev_stat[i] & 0x03) == 0x03)&&
                     ( outdata.all_temperatures[i] > TempObj.Temp_OW_threshold[i]))
                {
                    /*
                    ** VessApp CPU temperature is not stable, it may jump for over 3
                    ** degrees between 2 times temperature monitoring and soon be lower
                    ** than threshold, we try to check 2 times for make sure the
                    ** temperature is 'really' over warning temperaure threshold
                    */

                    /*
                    ** check if the previous temperature is also over warning temperaure
                    ** threshold, the value should not be ENC_TEMP_INVALID_VALUE
                    */

                    if (TempObj.prev_temp[i] > TempObj.Temp_OW_threshold[i] &&
                       !((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {
                        TempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear OC, UC and UW */
                        TempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                        Console.WriteLine("2nd time over warn-threshold.\n");
                        if ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) != Enclsoure_Constants.ENC_TEMP_STAT_OW)
                        {
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                                I2connection_Events.EVT_CODE_TEMP_ABOVE_WARNING,
                                                Convert.ToUInt32(i));
                        }

                    }
                    else if (!((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {

                        Console.WriteLine("1nd time over warn-threshold.\n");
                    }
                    else
                    {
                        Console.WriteLine("cool down but don't change fan");
                    }
                }
           else if(((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                     ( outdata.all_temperatures[i] < TempObj.Temp_OC_threshold[i]) &&
                     ( outdata.all_temperatures[i] > (TempObj.Temp_OW_threshold[i] - TempObj.hys_temp[i]))&&
                     ( TempObj.prev_temp[i] < TempObj.Temp_OC_threshold[i]) &&
                     ( TempObj.prev_temp[i] > (TempObj.Temp_OW_threshold[i] - TempObj.hys_temp[i])))
                {
                    /* Over critical -> over warning */
                    TempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    TempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW| Enclsoure_Constants.ENC_TEMP_STAT_UC;
                    Console.WriteLine("Joel : Over critical -> over warning.\n");
                }
           else if((((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) ||
                    ( TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                    ( outdata.all_temperatures[i]<=(TempObj.Temp_OW_threshold[i]-TempObj.hys_temp[i]))&&
                    ( TempObj.prev_temp[i] <= (TempObj.Temp_OW_threshold[i]-TempObj.hys_temp[i])))
                {
                    /* Over warning/critical to normal */
                    TempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC|
                                             Enclsoure_Constants.ENC_TEMP_STAT_OW|
                                             Enclsoure_Constants.ENC_TEMP_STAT_UC|
                                             Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    TempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_UW;
                    Console.WriteLine("Joel : Over warning -> normal.\n");
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                          I2connection_Events.EVT_CODE_TEMP_RETURNED_TO_NORMAL,
                                          Convert.ToUInt32(i));
                }
                else
                {
                    /* Over warning/critical to normal */


                }

                //check temp[i] is over critical 1min?
                if ((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC)
                {
                  if((DateTime.Now-TempObj.Controller_OC_time[i]).Ticks > (60 * 10000000))
                    {
                         I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                          I2connection_Events.EVT_CODE_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU,
                                          Convert.ToUInt32(i));
                    }
                }
                else
                {
                    TempObj.Controller_OC_time[i] = DateTime.Now;
                }
            }
        }
        #endregion

        #region acrroding Controller status to change fan
        private void ProcessTemperatureSts()
        {
            // Console.WriteLine("FAN_LEVEL=0x{0:x}", FAN_LEVEL);
            uint fanID = FAN_MASK_CPU | FAN_MASK_SYS;
            for (int i = 0; i < outdata.all_temperatures.Length; i++)
            {
                //if (i == 0)
                //fanID = FAN_MASK_SYS;

                if (((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                    ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC))
                {
                    //FAN MAX
                    Console.WriteLine("FAN MAX.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN MAX. Temp[" + i + "]=" + outdata.all_temperatures[i]);
                    //AUTO_FAN(0xF| fanID);
                    Fan_control_flag |= FAN_Max;
                }
                else if (!((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                         ((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                        !((TempObj.prev_stat[i] & 0x03) == 0x03) &&
                        !((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                {
                    //fan increase
                    Console.WriteLine("FAN increase.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN increase.Temp[" + i + "]=" + outdata.all_temperatures[i]);
                    Fan_control_flag |= FAN_Increase;
                    //AUTO_FAN(0x1| fanID);
                }
                /* else if (!((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                          !((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                           ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) |
                           ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW))
                 {
                     //fan decrease   /Enclsoure_Constants.ENC_TEMP_STAT_UW
                     Console.WriteLine("FAN decrease.\n");
                 }*/
                else if (((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UW) == Enclsoure_Constants.ENC_TEMP_STAT_UW))
                {
                    //if Fan to standard mode then Cur_stat ~ UW;
                    Console.WriteLine("FAN decrease.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN decrease.Temp[" + i + "]=" + outdata.all_temperatures[i]);
                    //AUTO_FAN(0x2| fanID);
                    Fan_control_flag |= FAN_Decrease;
                    if (FAN_LEVEL == FAN_Default_LEVEL + 1)
                    {
                        TempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    }
                }
            }
        }
        #endregion
        #endregion

        ///////////////////////////////
        ///    HDD thermal handle   ///
        ///////////////////////////////
        #region PD thermal  

        #region Check PD temp status 
        public void CheckPDTEMPstatus()
        {
            bool HDD_OC_detect = false;
            for (int i = 0; i < I2connection.NumOfHDSlots; i++)
            {
                //Console.WriteLine("outdata.all_temperatures[{0}] = {1} ", i, HDD_temp.cur_temp[i]);
                if (HDD_temp.cur_temp[i] == 0xff)//HDD temp invalid
                    continue;
                /*with out previous status*/
                if (HDD_temp.prev_temp[i] == Enclsoure_Constants.ENC_TEMP_INVALID_VALUE)
                {
                    if (HDD_temp.cur_temp[i] >= HDD_temp.HDD_OC_threshold[i])
                    {
                        HDD_temp.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_OW);
                    }
                    else if (HDD_temp.cur_temp[i] >= HDD_temp.HDD_OW_threshold[i])
                    {
                        HDD_temp.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                    }
                    else
                    {
                        HDD_temp.cur_stat[i] = 0;
                    }
                    continue;
                }
                if (!((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                     (HDD_temp.prev_temp[i] >= HDD_temp.HDD_OC_threshold[i]) &&
                     (HDD_temp.cur_temp[i] >= HDD_temp.HDD_OC_threshold[i]))
                {
                    /* Normal/Over warning  -> Over critical */
                    HDD_temp.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear UC and UW */
                    HDD_temp.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OW | Enclsoure_Constants.ENC_TEMP_STAT_OC);
                    if ((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) != Enclsoure_Constants.ENC_TEMP_STAT_OC)
                    {
                        Console.WriteLine("Joel : Normal/Over warning -> Over critical.\n");
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_PHYSICAL_DISK,
                                              I2connection_Events.EVT_CODE_PD_HI_CRITICAL_TEMP_OVER,
                                              Convert.ToUInt32(i));
                        HDD_temp.PD_OC_time[i] = DateTime.Now;
                    }
                }
                else if (!((HDD_temp.prev_stat[i] & 0x03) == 0x03) &&
                          (HDD_temp.cur_temp[i] > HDD_temp.HDD_OW_threshold[i]))
                {
                    /*
                    ** VessApp CPU temperature is not stable, it may jump for over 3
                    ** degrees between 2 times temperature monitoring and soon be lower
                    ** than threshold, we try to check 2 times for make sure the
                    ** temperature is 'really' over warning temperaure threshold
                    */

                    /*
                    ** check if the previous temperature is also over warning temperaure
                    ** threshold, the value should not be ENC_TEMP_INVALID_VALUE
                    */

                    if (HDD_temp.prev_temp[i] > HDD_temp.HDD_OW_threshold[i] &&
                       !((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {
                        HDD_temp.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear OC, UC and UW */
                        HDD_temp.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                        Console.WriteLine("2nd time over warn-threshold.\n");
                        if ((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) != Enclsoure_Constants.ENC_TEMP_STAT_OW)
                        {
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_PHYSICAL_DISK,
                                              I2connection_Events.EVT_CODE_PD_TEMP_OVER,
                                              Convert.ToUInt32(i));
                        }
                    }
                    else if (!((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {

                        Console.WriteLine("1nd time over warn-threshold.\n");
                    }
                    else
                    {
                        Console.WriteLine("cool down but don't change fan");
                    }
                }
                else if (((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                          (HDD_temp.cur_temp[i] < HDD_temp.HDD_OC_threshold[i]) &&
                          (HDD_temp.cur_temp[i] > (HDD_temp.HDD_OW_threshold[i] - HDD_temp.hys_temp[i])) &&
                          (HDD_temp.prev_temp[i] < HDD_temp.HDD_OC_threshold[i]) &&
                          (HDD_temp.prev_temp[i] > (HDD_temp.HDD_OW_threshold[i] - HDD_temp.hys_temp[i])))
                {
                    /* Over critical -> over warning */
                    HDD_temp.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    HDD_temp.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW | Enclsoure_Constants.ENC_TEMP_STAT_UC;
                    Console.WriteLine("Joel : Over critical -> over warning.\n");
                }
                else if ((((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) ||
                         (HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                         (HDD_temp.cur_temp[i] <= (HDD_temp.HDD_OW_threshold[i] - HDD_temp.hys_temp[i])) &&
                         (HDD_temp.prev_temp[i] <= (HDD_temp.HDD_OW_threshold[i] - HDD_temp.hys_temp[i])))
                {
                    /* Over warning/critical to normal */
                    HDD_temp.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_OW |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    HDD_temp.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_UW;
                    Console.WriteLine("Joel : Over warning -> normal.\n");
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_PHYSICAL_DISK,
                                          I2connection_Events.EVT_CODE_PD_TEMP_RETURNED_TO_NORMAL,
                                          Convert.ToUInt32(i));
                }
                else
                {
                    /* Over warning/critical to normal */
                }
                if ((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC)
                {
                    // blink flag on;
                    HDD_OC_detect = true;

                    if ((DateTime.Now - HDD_temp.PD_OC_time[i]).Ticks > (60 * 10000000))
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_PHYSICAL_DISK,
                                         I2connection_Events.EVT_CODE_PD_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU,
                                         Convert.ToUInt32(i));
                    }
                }
                else
                {
                    HDD_temp.PD_OC_time[i] = DateTime.Now;
                }
            }

            HDD_OC_blink = HDD_OC_detect;
        }
        #endregion

        #region acrroding PS status to change fan flag
        private void ProcessPDTemperatureSts()
        {
            // Console.WriteLine("FAN_LEVEL=0x{0:x}", FAN_LEVEL);
            for (int i = 0; i < I2connection.NumOfHDSlots; i++)
            {
                if (((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                    ((HDD_temp.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC))
                {
                    //FAN MAX
                    Console.WriteLine("FAN MAX.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN MAX.HDD Temp[" + i + "]=" + HDD_temp.cur_temp[i]);
                    Fan_control_flag |= FAN_Max;
                    // AUTO_FAN(0xF| FAN_MASK_SYS);
                    // break;
                }
                else if (!((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                         ((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                        !((HDD_temp.prev_stat[i] & 0x03) == 0x03) &&
                        !((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                {
                    //fan increase
                    Console.WriteLine("FAN increase.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN increase.HDD Temp[" + i + "]=" + HDD_temp.cur_temp[i]);
                    Fan_control_flag |= FAN_Increase;
                    //AUTO_FAN(0x1| FAN_MASK_SYS);
                    // break;
                }
                /* else if (!((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                          !((TempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                           ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) |
                           ((TempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW))
                 {
                     //fan decrease   /Enclsoure_Constants.ENC_TEMP_STAT_UW
                     Console.WriteLine("FAN decrease.\n");
                 }*/
                else if (((HDD_temp.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UW) == Enclsoure_Constants.ENC_TEMP_STAT_UW))
                {
                    //if Fan to standard mode then Cur_stat ~ UW;
                    Console.WriteLine("FAN decrease.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN decrease.HDD Temp[" + i + "]=" + HDD_temp.cur_temp[i]);
                    Fan_control_flag |= FAN_Decrease;
                    //AUTO_FAN(0x2| FAN_MASK_SYS);
                    if (FAN_LEVEL == FAN_Default_LEVEL)
                    {
                        HDD_temp.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    }
                    //break;
                }
            }
        }
        #endregion

        #endregion

        ///////////////////////////////
        ///    PSU thermal handle   ///
        ///////////////////////////////
        #region PSU thermal

        #region Check PSU temp status
        public void CheckPSUTEMPstatus()
        {
            for (int i = 0; i < outdata.PSU_temperatures.Length; i++)
            {

                //Console.WriteLine("outdata.PSU_temperatures[{0}] = {1} ", i, outdata.PSU_temperatures[i]);
                // Console.WriteLine(" NOW  Temp_OW_threshold[{0}] : 0x{1}", i, PSU_tempObj.Temp_OW_threshold[i]);
                // Console.WriteLine(" NOW  Temp_OC_threshold[{0}] : 0x{1}", i, PSU_tempObj.Temp_OC_threshold[i]);
                /*with out previous status*/
                if (PSU_tempObj.prev_temp[i] == Enclsoure_Constants.ENC_TEMP_INVALID_VALUE)
                {
                    if (outdata.PSU_temperatures[i] >= PSU_tempObj.Temp_OC_threshold[i])
                    {
                        PSU_tempObj.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_OW);
#if eventOK
#error                  I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
#error                        I2connection_Events.EVT_CODE_TEMP_ABOVE_CRITICAL,
#error                       Convert.ToUInt32(i));
#endif
                    }
                    else if (outdata.PSU_temperatures[i] >= PSU_tempObj.Temp_OW_threshold[i])
                    {
                        PSU_tempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                              I2connection_Events.EVT_CODE_TEMP_ABOVE_WARNING,
                                              Convert.ToUInt32(i));
                    }
                    else
                    {
                        PSU_tempObj.cur_stat[i] = 0;
                    }
                    continue;
                }
                if (!((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                     (PSU_tempObj.prev_temp[i] >= PSU_tempObj.Temp_OC_threshold[i]) &&
                     (outdata.PSU_temperatures[i] >= PSU_tempObj.Temp_OC_threshold[i]))
                {
                    /* Normal/Over warning  -> Over critical */
                    PSU_tempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear UC and UW */
                    PSU_tempObj.cur_stat[i] |= (Enclsoure_Constants.ENC_TEMP_STAT_OW | Enclsoure_Constants.ENC_TEMP_STAT_OC);
                    if ((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) != Enclsoure_Constants.ENC_TEMP_STAT_OC)
                    {
                        Console.WriteLine("Joel : Normal/Over warning -> Over critical.\n");
#if eventOK
#error                       I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
#error                                           I2connection_Events.EVT_CODE_TEMP_ABOVE_CRITICAL,
#error                       Convert.ToUInt32(i));
#endif
                        PSU_tempObj.Controller_OC_time[i] = DateTime.Now; ////update time base;
                    }
                }
                else if (!((PSU_tempObj.prev_stat[i] & 0x03) == 0x03) &&
                          (outdata.PSU_temperatures[i] > PSU_tempObj.Temp_OW_threshold[i]))
                {
                    /*
                    ** VessApp CPU temperature is not stable, it may jump for over 3
                    ** degrees between 2 times temperature monitoring and soon be lower
                    ** than threshold, we try to check 2 times for make sure the
                    ** temperature is 'really' over warning temperaure threshold
                    */

                    /*
                    ** check if the previous temperature is also over warning temperaure
                    ** threshold, the value should not be ENC_TEMP_INVALID_VALUE
                    */

                    if (PSU_tempObj.prev_temp[i] > PSU_tempObj.Temp_OW_threshold[i] &&
                       !((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {
                        PSU_tempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);/* clear OC, UC and UW */
                        PSU_tempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW;
                        Console.WriteLine("2nd time over warn-threshold.\n");
                        if ((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) != Enclsoure_Constants.ENC_TEMP_STAT_OW)
                        {
#if eventOK
#error                           I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
#error                            I2connection_Events.EVT_CODE_TEMP_ABOVE_WARNING,
#error                           Convert.ToUInt32(i));
#endif
                        }

                    }
                    else if (!((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                    {

                        Console.WriteLine("1nd time over warn-threshold.\n");
                    }
                    else
                    {
                        Console.WriteLine("cool down but don't change fan");
                    }
                }
                else if (((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                          (outdata.PSU_temperatures[i] < PSU_tempObj.Temp_OC_threshold[i]) &&
                          (outdata.PSU_temperatures[i] > (PSU_tempObj.Temp_OW_threshold[i] - PSU_tempObj.hys_temp[i])) &&
                          (PSU_tempObj.prev_temp[i] < PSU_tempObj.Temp_OC_threshold[i]) &&
                          (PSU_tempObj.prev_temp[i] > (PSU_tempObj.Temp_OW_threshold[i] - PSU_tempObj.hys_temp[i])))
                {
                    /* Over critical -> over warning */
                    PSU_tempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC | Enclsoure_Constants.ENC_TEMP_STAT_UC | Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    PSU_tempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_OW | Enclsoure_Constants.ENC_TEMP_STAT_UC;
                    Console.WriteLine("Joel : Over critical -> over warning.\n");
                }
                else if ((((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) ||
                         (PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                         (outdata.PSU_temperatures[i] <= (PSU_tempObj.Temp_OW_threshold[i] - PSU_tempObj.hys_temp[i])) &&
                         (PSU_tempObj.prev_temp[i] <= (PSU_tempObj.Temp_OW_threshold[i] - PSU_tempObj.hys_temp[i])))
                {
                    /* Over warning/critical to normal */
                    PSU_tempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_OC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_OW |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UC |
                                             Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    PSU_tempObj.cur_stat[i] |= Enclsoure_Constants.ENC_TEMP_STAT_UW;
                    Console.WriteLine("Joel : Over warning -> normal.\n");
                    I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                          I2connection_Events.EVT_CODE_TEMP_RETURNED_TO_NORMAL,
                                          Convert.ToUInt32(i));
                }
                else
                {
                    /* Over warning/critical to normal */


                }

                //check temp[i] is over critical 1min?
                if ((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC)
                {
                    if ((DateTime.Now - PSU_tempObj.Controller_OC_time[i]).Ticks > (60 * 10000000))
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_TEMPERATURE,
                                         I2connection_Events.EVT_CODE_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU,
                                         Convert.ToUInt32(i));
                    }
                }
                else
                {
                    PSU_tempObj.Controller_OC_time[i] = DateTime.Now;
                }
            }
        }
#endregion

#region acrroding PSU status to change fan
        private void ProcessPSUTemperatureSts()
        {
            // Console.WriteLine("FAN_LEVEL=0x{0:x}", FAN_LEVEL);
            uint fanID = FAN_MASK_CPU | FAN_MASK_SYS;
            for (int i = 0; i < outdata.PSU_temperatures.Length; i++)
            {
                //if (i == 0)
                //fanID = FAN_MASK_SYS;

                if (((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                    ((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC))
                {
                    //FAN MAX
                    Console.WriteLine("FAN MAX.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN MAX. PSUTemp[" + i + "]=" + outdata.PSU_temperatures[i]);
                    //AUTO_FAN(0xF| fanID);
                    Fan_control_flag |= FAN_Max;
                }
                else if (!((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                         ((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                        !((PSU_tempObj.prev_stat[i] & 0x03) == 0x03) &&
                        !((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UC) == Enclsoure_Constants.ENC_TEMP_STAT_UC))
                {
                    //fan increase
                    Console.WriteLine("FAN increase.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN increase.PSUTemp[" + i + "]=" + outdata.PSU_temperatures[i]);
                    Fan_control_flag |= FAN_Increase;
                    //AUTO_FAN(0x1| fanID);
                }
                /* else if (!((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) &&
                          !((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW) &&
                           ((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OC) == Enclsoure_Constants.ENC_TEMP_STAT_OC) |
                           ((PSU_tempObj.prev_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_OW) == Enclsoure_Constants.ENC_TEMP_STAT_OW))
                 {
                     //fan decrease   /Enclsoure_Constants.ENC_TEMP_STAT_UW
                     Console.WriteLine("FAN decrease.\n");
                 }*/
                else if (((PSU_tempObj.cur_stat[i] & Enclsoure_Constants.ENC_TEMP_STAT_UW) == Enclsoure_Constants.ENC_TEMP_STAT_UW))
                {
                    //if Fan to standard mode then Cur_stat ~ UW;
                    Console.WriteLine("FAN decrease.\n");
                    Prom_Enclosure_Serives.Log_File.FileLog("FAN decrease.PSUTemp[" + i + "]=" + outdata.PSU_temperatures[i]);
                    //AUTO_FAN(0x2| fanID);
                    Fan_control_flag |= FAN_Decrease;
                    if (FAN_LEVEL == FAN_Default_LEVEL + 1)
                    {
                        PSU_tempObj.cur_stat[i] &= ~(Enclsoure_Constants.ENC_TEMP_STAT_UW);
                    }
                }
            }
        }
#endregion
#endregion

        private void UpdatePrevTempObjStat()
        {
            for (int i = 0; i < outdata.all_temperatures.Length; i++)
            {
                Console.WriteLine("cur_stat{2}=0x{0:x}  ,pre_stat{2}={1:x}", TempObj.cur_stat[i], TempObj.prev_stat[i],i);
                TempObj.prev_temp[i] = outdata.all_temperatures[i];
                TempObj.prev_stat[i] = TempObj.cur_stat[i];
            }
            for (int i = 0; i < HDD_temp.cur_temp.Length; i++)
            {
               // Console.WriteLine("HDD cur_stat{2}=0x{0:x}  ,HDD pre_stat{2}={1:x}", HDD_temp.cur_stat[i], HDD_temp.prev_stat[i], i);
                HDD_temp.prev_temp[i] = HDD_temp.cur_temp[i];
                HDD_temp.prev_stat[i] = HDD_temp.cur_stat[i];
            }
            for (int i = 0; i < outdata.PSU_temperatures.Length; i++)
            {
                PSU_tempObj.prev_temp[i] = outdata.PSU_temperatures[i];
                PSU_tempObj.prev_stat[i] = PSU_tempObj.cur_stat[i];
            }
        }

        private void AUTO_FAN(uint status)
        {
            uint FanID= status & (FAN_MASK_SYS | FAN_MASK_CPU);
            uint Control = status & (~FAN_MASK_SYS | ~FAN_MASK_CPU);

            switch (Control)
            {
                case FAN_Max://MAX FAN
                    if(FAN_LEVEL!=0xF)
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                         I2connection_Events.EVT_CODE_COOLING_DEVICE_SPEED_INCREASED,
                                         0);
                    }
                    FAN_LEVEL =0xf;
                    NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_CPUTIN, 0xf);
                    if (Model_ID != Model_VA8020)
                    {
                        NCT7802_BP.Nct7802y_set_fan_speed(NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL, 0xf);
                    }
                    else
                    {
                        NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_SYSTIN, FAN_LEVEL);
                        //NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_AUXTIN, FAN_LEVEL);
                    }

                    Fan_control_flag = 0x01;
                    break;
                    

                case FAN_Increase://increase Fan
                    if (FAN_LEVEL != 0xF)
                    {
                        FAN_LEVEL += 1;
                        NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_CPUTIN, FAN_LEVEL);
                        if (Model_ID != Model_VA8020)
                        {
                            NCT7802_BP.Nct7802y_set_fan_speed(NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL, FAN_LEVEL);
                        }
                        else
                        {
                            NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_SYSTIN, FAN_LEVEL);
                        //    NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_AUXTIN, FAN_LEVEL);
                        }
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_SPEED_INCREASED,
                                                 0);
                    }
                    Fan_control_flag = 0x01;
                    break;

                case FAN_Decrease://decrease Fan
                    if (FAN_LEVEL != 0x0)
                    {
                        FAN_LEVEL -= 1;
                        FAN_LEVEL = FAN_LEVEL < FAN_Default_LEVEL ? FAN_Default_LEVEL : FAN_LEVEL ;
                        NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_CPUTIN, FAN_LEVEL);
                        if (Model_ID != Model_VA8020)
                        {
                            NCT7802_BP.Nct7802y_set_fan_speed(NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL, FAN_LEVEL);
                        }
                        else
                        {
                            NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_SYSTIN, FAN_LEVEL);
                         //   NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_AUXTIN, FAN_LEVEL);
                        }
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_COOLING_DEVICE,
                                              I2connection_Events.EVT_CODE_COOLING_DEVICE_SPEED_DECREASED,
                                                0);
                    }
                    break;

                default :
                    break;

            }
           // for(int i=0;i<outdata.all_temperatures.Length;i++)
           // NCT.Set_Fan(NCT6776_Constants.NCT6XXX_ENV_CTRL_FAN_SEN_CPUTIN, NCT.CPU_Fan_Level);

        }
        /*  ----Debug code ---- ****SHOW array*****
        public static void PrintIndexAndValues(uint?[] myArr,string name)
        {
            for (int i = 0; i < myArr.Length; i++)
            {
                Console.WriteLine(" {2}  [{0}] : 0x{1:x}", i, myArr[i],name);
            }
            Console.WriteLine();
        }

        public static void PrintIndexAndValuesDO(uint?[,] myArr, string name)
        {
            Console.WriteLine("!!!!{0}!!!", myArr.Length);
            Console.WriteLine(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            for (int i = 0; i < (myArr.Length/ myArr.Rank); i++)
            {
                Console.WriteLine(" {0}  [{1}][0] : 0x{2:x}",name,i,myArr[i,0]);
                Console.WriteLine(" {0}  [{1}][1] : 0x{2:x}", name, i, myArr[i, 1]);
            }
            Console.WriteLine();
            Console.WriteLine(" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }*/

        public void Enclosure_SET_fan(uint?[]  Date)
        {
                 uint CPU_SET_FAN = 0;
                 uint SYS_SET_FAN = 0;
            try
            {
                //Console.WriteLine("  Date len =  : 0x{0:x}", Date.Length);
                CPU_SET_FAN = (uint)Date[0];
                SYS_SET_FAN = (uint)Date[1];

                Console.WriteLine("  CPU_SET_FAN =  : 0x{0:x}", CPU_SET_FAN);
                Console.WriteLine("  SYS_SET_FAN =   : 0x{0:x}", SYS_SET_FAN);

                if (CPU_SET_FAN != 0)
                    NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_CPUTIN, CPU_SET_FAN);
                if (Model_ID != Model_VA8020)
                {
                    if (SYS_SET_FAN != 0)
                        NCT7802_BP.Nct7802y_set_fan_speed(NCT7802_Constants.NCT7802Y_2U8_BP_DEVICE_FAN_ALL, SYS_SET_FAN);
                }
                else
                {
                    if (SYS_SET_FAN != 0)
                    {
                        NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_SYSTIN, SYS_SET_FAN);
                       // NCT.Set_Fan(NCT5567_Constants.NCT5567_ENV_CTRL_FAN_SEN_AUXTIN, SYS_SET_FAN);
                    }
                }
                for (int i = 0; i < Date.Length; i++)
                {
                    Console.WriteLine("   [{0}] : 0x{1:x}", i, Date[i]);
                    //      if (i == 0 && (program.GetRegFan[i] != 0))
                    //           program.NCT.Set_Fan(0x00, (uint)program.GetRegFan[i]);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Enclosure_SET_fan fail:{0}", ex);
            }
        }

        public void Enclosure_SET_Control_Temp_threshold(uint?[] Date)
        {
            //(TempObj.Temp_OW_threshold
            uint OW_temp = 0, OC_temp = 0;
            OW_temp= (uint)Date[0] < 45 ? 45 : (uint)Date[0];
            OC_temp = (uint)Date[1] > OW_temp ? (uint)Date[1] : OW_temp + 0x5;
            try
            {
                for (int i = 0; i < TempObj.Temp_OW_threshold.Length; i++)
                {

                    TempObj.Temp_OW_threshold[i] = OW_temp;
                    TempObj.Temp_OC_threshold[i] = OC_temp;
                    Console.WriteLine(" SET Controller Temp_OW_threshold[{0}] : 0x{1}", i, TempObj.Temp_OW_threshold[i]);
                    Prom_Enclosure_Serives.Log_File.FileLog(" SET Controller Temp_OW_threshold["+ i+"] : " + TempObj.Temp_OW_threshold[i]);
                    Console.WriteLine(" SET Controller Temp_OC_threshold[{0}] : 0x{1}", i, TempObj.Temp_OC_threshold[i]);
                    Prom_Enclosure_Serives.Log_File.FileLog(" SET Controller Temp_OC_threshold[" + i + "] : " + TempObj.Temp_OC_threshold[i]);
                }
                Enclsoure_class.Temp_OC_threshold = OC_temp;
                Enclsoure_class.Temp_OW_threshold = OW_temp;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Enclosure_SET_Temp_threshold fail:{0}", ex);
            }
        }

        public void Enclosure_SET_HDD_Temp_threshold(uint?[] Date)
        {
            //(TempObj.Temp_OW_threshold
            uint OW_temp = 0, OC_temp = 0;
            OW_temp= (uint)Date[0] < 45 ? 45 : (uint)Date[0];
            OC_temp= (uint)Date[1] > OW_temp ? (uint)Date[1] : OW_temp + 0x5;
            try
            {
                for (int i = 0; i < HDD_temp.HDD_OW_threshold.Length; i++)
                {

                    HDD_temp.HDD_OW_threshold[i] = OW_temp;
                    HDD_temp.HDD_OC_threshold[i] = OC_temp;

                    Console.WriteLine(" SET PD Temp_OW_threshold[{0}] : 0x{1}", i, HDD_temp.HDD_OW_threshold[i]);
                    Prom_Enclosure_Serives.Log_File.FileLog(" SET PD Temp_OW_threshold[" + i + "] : " + HDD_temp.HDD_OW_threshold[i]);
                    Console.WriteLine(" SET PD Temp_OC_threshold[{0}] : 0x{1}", i, HDD_temp.HDD_OC_threshold[i]);
                    Prom_Enclosure_Serives.Log_File.FileLog(" SET PD Temp_OC_threshold[" + i + "] : " + HDD_temp.HDD_OC_threshold[i]);
                    // Console.WriteLine(" SET  Temp_OW_threshold[{0}] : 0x{1}", i, TempObj.Temp_OW_threshold[i]);
                    // Console.WriteLine(" SET  Temp_OC_threshold[{0}] : 0x{1}", i, TempObj.Temp_OC_threshold[i]);
                }
                Enclsoure_class.HDD_OW_threshold = OW_temp;
                Enclsoure_class.HDD_OC_threshold = OC_temp;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Enclosure_SET_HDD_Temp_threshold fail:{0}", ex);
            }
        }

        // public void Blink(Object source, ElapsedEventArgs e)
        private static bool Blink_flag = false;
        public void Locate_Blink()
        {
            HDD_OC_blink = false;
            DateTime start_time = DateTime.Now;
            TimeSpan time_over;
            Blink_trigger = true;
              Blink_flag = !Blink_flag;
            uint i;
                do
                {
                ////light off
                    bool check = Blink_flag;
                    i = (~(TCA6416.A20P0 & Locatemask[0, 0])) & TCA6416.A20P0;
                    tca6416.tca6416a_set_gpio_port_value(0x20, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(5);
                    i = (~(TCA6416.A20P1 & Locatemask[0, 1])) & TCA6416.A20P1;
                    tca6416.tca6416a_set_gpio_port_value(0x20, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(5);
                    i = (~(TCA6416.A21P0 & Locatemask[1, 0])) & TCA6416.A21P0;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(5);
                    i = (~(TCA6416.A21P1 & Locatemask[1, 1])) & TCA6416.A21P1;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(1000);
                    ////light on
                    i = (TCA6416.A20P0 & Locatemask[0, 0])| TCA6416.A20P0;
                    tca6416.tca6416a_set_gpio_port_value(0x20, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(5);
                    i = TCA6416.A20P1 & Locatemask[0, 1]| TCA6416.A20P1;
                    tca6416.tca6416a_set_gpio_port_value(0x20, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(5);
                    i = TCA6416.A21P0 & Locatemask[1, 0]| TCA6416.A21P0;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(5);
                    i = TCA6416.A21P1 & Locatemask[1, 1]| TCA6416.A21P1;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(1000);
                    time_over = DateTime.Now- start_time;
                    if (check != Blink_flag)
                        return;
                    if (time_over.Ticks> 60 * 10000000)
                    {
                        Blink_flag = false;
                        Blink_trigger = false;
                        return;
                    }
                } while (true);
            
        }
        public void PD_OC_Blink()
        {
            uint i;
            if (GlobeError_LED_trigger == false)
            {
                tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_GLOBE_ERR, TCA6416_Constants.ENC_LED_RED);
            }

            do
            {
                ////light off
                if (Model_ID == Model_VA8020)
                {
                    i = (~(TCA6416.A21P0 & 0x0C)) & TCA6416.A21P0;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(1000);
                    ////light on
                    i = (TCA6416.A21P0 & 0x0C) | TCA6416.A21P0;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_0, ref i);
                    Thread.Sleep(1000);
                }
                else
                {
                    i = (~(TCA6416.A21P1 & 0x03)) & TCA6416.A21P1;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(1000);
                    ////light on
                    i = (TCA6416.A21P1 & 0x03) | TCA6416.A21P1;
                    tca6416.tca6416a_set_gpio_port_value(0x21, TCA6416_Constants.TCA6416A_PORT_1, ref i);
                    Thread.Sleep(1000);
                }

            } while (HDD_OC_blink && !(Blink_trigger));//while ( HDD_OC_blink && (Blink_trigger==false));
            if (GlobeError_LED_trigger == false)
            {
                tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_GLOBE_ERR, TCA6416_Constants.ENC_LED_GREEN);
                Console.WriteLine("PD_OC_Blink finish and change GLOBE_ERR to green");
            }
        }

        public void Enclosure_SET_led(uint?[] Date)
        {
            uint chipId;
            uint port0_data;
            uint port1_data;
            for (uint i = 0; i < Date.GetLength(0); i++)
            {
                chipId = i;
                Console.WriteLine("Date=[{0:x}]", Date[i]);
                port0_data = (uint)((Date[i] & 0xFF00) >> 8);
                port1_data = (uint)Date[i] & 0x00FF;
                Console.WriteLine("chipId=[{0}]", chipId);
                Console.WriteLine("port0=[{0:x}]", port0_data);
                
                Console.WriteLine("port1=[{0:x}]", port1_data);
                tca6416.encSetLedStatus(chipId, TCA6416_Constants.TCA6416A_PORT_0, port0_data);
                tca6416.encSetLedStatus(chipId, TCA6416_Constants.TCA6416A_PORT_1, port1_data);
            }

        }

        public void Enclosure_GET_led()
        {
            tca6416.encGetLedStatus(ref TCA_leds);
           // Console.WriteLine("Length=[{0:x}]", TCA_leds.Length);
            Array.Copy(TCA_leds, outdata.all_leds, TCA_leds.Length);
            //sensorData.Add("Led", outdata.all_leds);
            /*
			for(int i=0; i < TCA_leds.Length; i++)
			{
				Console.WriteLine("TCA_leds=[{0:x}]", TCA_leds[i]);
				Console.WriteLine("all_leds=[{0:x}]", outdata.all_leds[i]);
			}
			*/
        }
        private void Fan_LED_control()
        {
            if (FAN_LED_trigger == true)
            {
                if (Fan_error == 0)
                {
                    Console.WriteLine("Fan_error=0");
                    Prom_Enclosure_Serives.Log_File.FileLog("Fan_error=0");
                    tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_FAN, TCA6416_Constants.ENC_LED_GREEN);
                    if (GlobeError_LED_trigger == false)
                    { tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_GLOBE_ERR, TCA6416_Constants.ENC_LED_GREEN); }
                    Fan_color = TCA6416_Constants.ENC_LED_GREEN;
                }
               /* else if (Fan_error == 1)
                {
                    Console.WriteLine("Fan_error=1");
                    Prom_Enclosure_Serives.Log_File.FileLog("Fan_error=1");
                    tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_FAN, TCA6416_Constants.ENC_LED_AMBER);
                    if (GlobeError_LED_trigger == false)
                    { tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_GLOBE_ERR, TCA6416_Constants.ENC_LED_GREEN); }
                    Fan_color = TCA6416_Constants.ENC_LED_AMBER;
                }*/
                else if (Fan_error >= 1)
                {
                    Console.WriteLine("Fan_error>1");
                    Prom_Enclosure_Serives.Log_File.FileLog("Fan_error>=1;FAN_error="+ Fan_error);
                    tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_FAN, TCA6416_Constants.ENC_LED_RED);
                    if (GlobeError_LED_trigger == false)
                    { tca6416.NCT6414_FAN_Control(TCA6416_Constants.ENC_LED_GLOBE_ERR, TCA6416_Constants.ENC_LED_RED); }
                    Fan_color = TCA6416_Constants.ENC_LED_RED;
                }
                FAN_LED_trigger = false;
            }
            for (uint i = 0; i < PSU_Constants.PSU_NUM; i++)
            {
                if (PSU.Status.PRESENT[i] == false||
                    PSU.Status.OPERATIONAL[i]==false||
                    ((PSU_tempObj.cur_stat[i]& Enclsoure_Constants.ENC_TEMP_STAT_OC)== Enclsoure_Constants.ENC_TEMP_STAT_OC))
                {
                    PSU.SetPSUGlobeErr(i,PSU_Constants.ENC_LED_RED);
                }
                else
                    PSU.SetPSUGlobeErr(i, PSU_Constants.ENC_LED_GREEN);
            }
        }

        public void VerifyPDtemp()
        {
            HDD.PDtemp_update(ref HDD_temp.cur_temp);
            for(int i=0;i<HDD_temp.cur_temp.Length; i++)
            {
                Console.WriteLine("Hdd_temp[{0}]={1}", i, HDD_temp.cur_temp[i]);
            }
        }


    }
}



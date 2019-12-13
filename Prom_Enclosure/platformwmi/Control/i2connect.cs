/*---------------------------------------------------------------------------**
**          Filename    : i2connect.cs                                       **
**          Description : connect to FW by i2 or pMic.cpp                    **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using System.Runtime.InteropServices;

namespace i2api
{
    static class I2connection_Constants
    {


        internal const uint I2B_API_RET_SUCCESS = 0x00;
        internal const uint I2B_API_RET_PARAM_ERR = 0x01;
        internal const uint I2B_API_RET_LOGIN_ERR = 0x02;
        internal const uint I2B_API_RET_CREATE_ERR = 0x03;
        internal const uint I2B_API_RET_I2API_ERR = 0x04;
        internal const uint I2B_API_RET_MEMALLOC_ERR = 0x05;
        internal const uint I2B_API_RET_UNSUPPORTED = 0x06;

        internal const uint I2B_API_RET_UNKNOWN = 0xFF;
    }

    static class I2connection_Events
    {
        //Classes
        internal const uint EVT_CLASS_COOLING_DEVICE = 0x0005;
        internal const uint EVT_CLASS_TEMPERATURE    = 0x001e;
        internal const uint EVT_CLASS_PHYSICAL_DISK = 0x000d;

        /* EVT_CLASS_COOLING_DEVICE             0x05 */
        internal const uint EVT_CODE_COOLING_DEVICE_STARTED = 0x00;
        internal const uint EVT_CODE_COOLING_DEVICE_STOPPED = 0x01;
        internal const uint EVT_CODE_COOLING_DEVICE_SPEED_INCREASED = 0x02;
        internal const uint EVT_CODE_COOLING_DEVICE_SPEED_DECREASED = 0x03;
        internal const uint EVT_CODE_COOLING_DEVICE_MALFUNCTIONING = 0x04;
        internal const uint EVT_CODE_COOLING_DEVICE_INSERTED = 0x05;
        internal const uint EVT_CODE_COOLING_DEVICE_REMOVED = 0x06;
        internal const uint EVT_CODE_COOLING_DEVICE_FUNCTIONAL = 0x07;
        internal const uint EVT_CODE_COOLING_DEVICE_NOT_INSTALLED = 0x08;
        internal const uint EVT_CODE_COOLING_DEVICE_UNKNOWN_STS = 0x09;
        /* END EVT_CLASS_COOLING_DEVICE         0x05 */

        /* EVT_CLASS_TEMPERATURE                0x1e */
        internal const uint EVT_CODE_TEMP_ABOVE_THRESHOLD = 0x00;   /* for V4 group */
        internal const uint EVT_CODE_TEMP_ABOVE_CRITICAL = 0x01;     /* for V4 group */
        internal const uint EVT_CODE_TEMP_ABOVE_WARNING = 0x02;     /* for V4 group */
        internal const uint EVT_CODE_TEMP_RETURNED_TO_NORMAL = 0x03;    /* for V4 group */
        internal const uint EVT_CODE_CTRL_TEMP_ABOVE_CRITICAL = 0x04;    /* for V4 group */
        internal const uint EVT_CODE_CTRL_TEMP_ABOVE_WARNING = 0x05;      /* for V4 group */
        internal const uint EVT_CODE_CTRL_TEMP_RETURNED_TO_NORMAL = 0x06;       /* for V4 group */
        internal const uint EVT_CODE_TEMP_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU = 0x07;
        /* EVT_CLASS_TEMPERATURE                0x1e */

        /* EVT_CLASS_PHYSICAL_DISK              0x0d */
        internal const uint EVT_CODE_PD_TEMP_OVER = 0x39;
        internal const uint EVT_CODE_PD_TEMP_RETURNED_TO_NORMAL = 0x3A;
        internal const uint EVT_CODE_PD_HI_CRITICAL_TEMP_OVER = 0x3B;
        internal const uint EVT_CODE_PD_ABOVE_PROTECTION_THRESHOLD_SHUTDOWN_PSU = 0x3D;  
        /* EVT_CLASS_PHYSICAL_DISK              0x0d */

    }

    public class I2connection
    {
        [DllImport("libi2bdg")]
        public static extern int i2bdg_setEvent(uint ClassEventID, uint CodeEventID, uint DeviceID, ref uint ExtraLog);

        [DllImport("libi2bdg")]
        public static extern int i2bApi_getHardDiskDriveInfo(IntPtr out_DataBuf, long in_BufLen);

        [DllImport("libi2bdg")]
        public static extern int i2bApi_getElementCnt(ref I2bElementCount_t out_DataBuf);

        [DllImport("pMic_entry.dll")]
        public static extern bool discover(ref uint pPortId, ref uint pConsoleId);

        [DllImport("pMic_entry.dll")]
        public static extern int SetEventMic(uint ClassEventID, uint CodeEventID, uint DeviceID, ref uint ExtraLog);

        [DllImport("pMic_entry.dll")]
        public static extern int PhysicalDriveInfo(IntPtr outdata, long in_BufLen,uint NumOfHDSlots);

        [DllImport("pMic_entry.dll")]
        public static extern IntPtr Get_event();

        [DllImport("Kernel32.dll")]
        public static extern void WaitForSingleObject(IntPtr eve,uint x);

        internal static uint NumOfHDSlots = 0;

        public static void Get_ElementCount()
        {
            I2bElementCount_t Init = new I2bElementCount_t();
            i2bApi_getElementCnt(ref Init);
         /* Console.WriteLine("NumOfHDSlots={0}", Convert.ToUInt32(Init.NumOfHDSlots));
            Console.WriteLine("NumOfFans={0}", Convert.ToUInt32(Init.NumOfFans));
            Console.WriteLine("NumOfVoltageSensors={0}", Convert.ToUInt32(Init.NumOfVoltageSensors));
            Console.WriteLine("NumOfTempSensors={0}", Convert.ToUInt32(Init.NumOfTempSensors));*/
            NumOfHDSlots = Convert.ToUInt32(Init.NumOfHDSlots);
        }

        public I2connection()
        {
            //init
        }

        public static void GetHardDiskDriveInfo(ref pMicHddInfo_t[] HDDinfo)
      //  public static void GetHardDiskDriveInfo()
        {
            try
            {
                int status = 0;
                int workStationCount = Convert.ToInt32(NumOfHDSlots);
                int size = Marshal.SizeOf(typeof(pMicHddInfo_t));
                IntPtr HDDinfoIntptr = Marshal.AllocHGlobal(size * workStationCount);
                HDDinfo = new pMicHddInfo_t[workStationCount];

                for (int i = 0; i < size * workStationCount; i++)//fillup 0 to buffer
                {
                    Marshal.WriteByte(HDDinfoIntptr, i, 0);
                }

                HDDinfo = new pMicHddInfo_t[workStationCount];


                //Console.WriteLine("===================tyrtyrty=====v1.4");
                status = PhysicalDriveInfo(HDDinfoIntptr, size * NumOfHDSlots, NumOfHDSlots);
                //Console.WriteLine("PhysicalDriveInfo__status={0}", status);
                for (int i = 0; i < workStationCount; i++)
                {
                    IntPtr ptr = (IntPtr)(HDDinfoIntptr + i * size);
                    HDDinfo[i] = (pMicHddInfo_t)Marshal.PtrToStructure(ptr, typeof(pMicHddInfo_t));
                }
                /*Console.WriteLine("HDDinfo.Length={0}", HDDinfo.Length);
                for (int i=0;i<HDDinfo.Length;i++)
                {
                    Console.WriteLine("HDDinfo[{0}].temperature={1}", i, Convert.ToInt32(HDDinfo[i].temperature));
                }*/
                Marshal.FreeHGlobal(HDDinfoIntptr);

            }
            catch(OverflowException ex)
            {
                Console.WriteLine("OverflowException FAIL={0}", ex);
                Prom_Enclosure_Serives.Log_File.FileLog("GetHardDiskDriveInfo_FAIL:" + Convert.ToString(ex));
            }
            catch (Exception ex)
            {
                Console.WriteLine("GetHardDiskDriveInfo_FAIL{0}", ex);
                Prom_Enclosure_Serives.Log_File.FileLog("GetHardDiskDriveInfo_FAIL:"+Convert.ToString(ex));
            }
        }

        public static bool SetEvent(uint ClassEventID, uint CodeEventID, uint DeviceID)
        {
            try
            { 
                    uint extra = 0;
                    int ret;
                    ret = SetEventMic(ClassEventID, CodeEventID, DeviceID, ref extra);

                    if (ret == I2connection_Constants.I2B_API_RET_SUCCESS)
                        return true;

                    Console.WriteLine("Set_event_fail={0}", ret);
                    return false;
            }

            catch (Exception ex)
            {
                Console.WriteLine("SetEvent_fail{0}", ex);
                return false;
            }
        }


    }

    //[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    [StructLayout(LayoutKind.Sequential)]
    public struct I2bHddInfo_t
    {
        public uint NumOfPD;                /* Tota Number of Physical Drive  */
        public ushort PDId;                /* Flat ID                        */
        public ushort drvType;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public byte[] driveModelNo;     /* Drive Model Number             */
        public long confCapacity;        /* configurable capacity          */
        public ushort enclosureId;
        public ushort slotId;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] opStatus;         /* Operation Status string        */
        public uint opStatusFlag;           /* Operation Status flag          */

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] configStatus;     /* Configuration Status string    */
        public char HDDTempWarThreshold;    /* PD temperature warning thershould */
        public char HDDTempCriThreshold;    /* PD temperature warning thershould */
        public char temperature;            /* PD temperature                 */
        public char TempStatusFlag;         /* PD temperature status          */

        public char controllerId;           /* PD belong to controller Id     */
        public ushort arrayId;                /* PD belong to array Id          */
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct pMicHddInfo_t
    {
        public uint NumOfPD;                /* Tota Number of Physical Drive  */
        public ushort PDId;                /* Flat ID                        */
        public ushort drvType;
        public long confCapacity;        /* configurable capacity          */
        public ushort enclosureId;
        public ushort slotId;
        //public char HDDTempWarThreshold;    /* PD temperature warning thershould */
        //public char HDDTempCriThreshold;    /* PD temperature warning thershould */
        public char temperature;            /* PD temperature                 */
       // public char TempStatusFlag;         /* PD temperature status          */
        public char controllerId;           /* PD belong to controller Id     */
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct I2bElementCount_t
    {
        public char NumOfMB;
        public char NumOfSep;
        public char NumOfPsus;
        public char NumOfCUs;

        public char NumOfFans;
        public char NumOfTempSensors;
        public char NumOfVoltageSensors;
        public char NumOfAudibleAlarms;

        public char NumOfBatteries;
        public char NumOfHDSlots;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        byte[] reserved;
    }
}



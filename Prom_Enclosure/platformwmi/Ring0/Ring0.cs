/*---------------------------------------------------------------------------**
**          Filename    : Ring0.cs                                           **
**          Description : create class for control Ring0 & Enclosure         **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/

using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security.AccessControl;
using System.Threading;
using System.Text;
using OpenLibSys;


namespace WingRing
{
    public static class Ring0
    {
        public static Ols ols = new Ols();

        public static void Init()
        {
          //  int status;
           // status= ols.InitializeOls();
            //Console.WriteLine("InitializeOls={0:x}", status);
            //ols = new OpenLibSys.Ols();
            // old.GetStatus() == (uint)Ols.Status.NO_ERROR;
        }

        public static void WriteIoPort(uint port, byte value)
        {
            
            ols.WriteIoPortByte(port, value);
        }

        public static byte ReadIoPort(uint port)
        {

            return (byte)ols.ReadIoPortByte(port);
        }

        public static bool ReadPciConfig(uint pciAddress, uint regAddress, out uint value)
        {


            value = 0;
            value = ols.ReadPciConfigDword(pciAddress,Convert.ToByte(regAddress));
            return  true;
        }
        public static bool WritePciConfig(uint pciAddress, uint regAddress,uint value)
        {

            ols.WritePciConfigDword(pciAddress, regAddress, Convert.ToByte(value));
            return true;
        }

        public static void Test()
        {
            uint eax = 0, edx = 0;
           // ols.Rdmsr(uint index, ref uint eax, ref uint edx);
            ols.Rdmsr(0x19C, ref eax, ref edx);
            Console.WriteLine("eax={0:x},edx={1:x}", eax, edx);
            ols.Rdmsr(0x1A2, ref eax, ref edx);
            Console.WriteLine("eax={0:x},edx={1:x}", eax, edx);

        }
        public static bool RdMsr(uint index, ref uint eax, ref uint edx)
        {
            if( ols.Rdmsr(index, ref eax, ref edx) == 0 )
                return true;
           // Console.WriteLine("RdMSR status={0:x}", status);
            return false;
        }
    }
}

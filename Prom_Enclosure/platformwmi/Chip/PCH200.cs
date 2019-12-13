/*---------------------------------------------------------------------------**
**          Filename    : PCH200.cs                                          **
**          Description : implement PCH function                             **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using System.Threading;
using System.Globalization;
using System.Text;
using WingRing;
using i2api;




namespace Chip.Contrl
{
    public static class PCHSMBUS
    {
       private static uint SMBHSTSTS = 0;
	   private static uint SMBHSTCNT = 0;
	   private static uint SMBHSTCMD = 0;
	   private static uint SMBHSTADD = 0;
	   private static uint SMBHSTDAT0 = 0;
	   private static uint SMBHSTDAT1 = 0;
	   private static uint SMBBLKDAT = 0;
	   private static uint SMBPEC = 0;
	   private static uint SMBAUXSTS = 0;
	   private static uint SMBAUXCTL = 0;
	   private static uint SMBusbase =0;

        /*follow PCI spec define smbus device and funtion*/
        private static uint PCI_address = (PCH_Constants.PCH200_LPC_DEVICE_NUMBER << 3) | PCH_Constants.PCH200_SMBUS_FUNCTION_NUMBER_SKYLAKE;

        public static void PCHSMBUS_init()
        {
            //Ring0.Open();

			/* to get SMBus IO space */
			Ring0.ReadPciConfig(PCI_address, PCH_Constants.PCH200_SMB_BASE, out SMBusbase);
            SMBusbase &=0x0000ffe0;
            Console.WriteLine("SMBusbase={0:x}", SMBusbase);
            /*Define function offset*/
            SMBHSTSTS  = 0  + SMBusbase;
			SMBHSTCNT  = 2  + SMBusbase;
			SMBHSTCMD  = 3  + SMBusbase;
			SMBHSTADD  = 4  + SMBusbase;
			SMBHSTDAT0 = 5  + SMBusbase;
			SMBHSTDAT1 = 6  + SMBusbase;
			SMBBLKDAT  = 7  + SMBusbase;
			SMBPEC     = 8  + SMBusbase;
			SMBAUXSTS  = 12 + SMBusbase;
			SMBAUXCTL  = 13 + SMBusbase;


            Model_check();

        }

        private static void Model_check()
        {
            uint[] data_temp = new uint[1];
            bool Model_check_result = false;
            switch (Enclsoure.Enclsoure_class.Model_ID)
            {
                case Enclsoure.Enclsoure_class.Model_VA8200:

                    if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3340, 0xF4, 1, ref data_temp) == 0)
                    {
                        if (!(ReadSMB(NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR, 0x00, 1, ref data_temp) == 0))
                        {
                            I2connection.NumOfHDSlots = 8;
                            Prom_Enclosure_Serives.Log_File.FileLog("Model Confirm is A8200");
                            Model_check_result = true;
                        }

                    }
                    break;
                case Enclsoure.Enclsoure_class.Model_VA8200D:
                    if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3340, 0xF4, 1, ref data_temp) == 0)
                    {
                        if (ReadSMB(NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR, 0x00, 1, ref data_temp) == 0)
                        {
                            I2connection.NumOfHDSlots = 8;
                            Prom_Enclosure_Serives.Log_File.FileLog("Model Confirm is A8200");
                            Model_check_result = true;
                        }
                            
                    }
                    break;
                case Enclsoure.Enclsoure_class.Model_VA8100:

                    if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3120, 0xF4, 1, ref data_temp) == 0)
                    {
                        I2connection.NumOfHDSlots = 4;
                        Prom_Enclosure_Serives.Log_File.FileLog("Model Confirm is A8100");
                        Model_check_result = true;
                    }
                    break;
                case Enclsoure.Enclsoure_class.Model_VA8020:

                    if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA8020, 0xF4, 1, ref data_temp) == 0)
                    {
                        I2connection.NumOfHDSlots = 2;
                        Prom_Enclosure_Serives.Log_File.FileLog("Model Confirm is A8020");
                        Model_check_result = true;
                    }
                    break;
                default:
                    break;

            }

            if (Model_check_result == false)
            {
                
                if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3340, 0xF4, 1, ref data_temp) == 0)
                {
                    if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3340, 0xF4, 1, ref data_temp) == 0)
                    {
                        Enclsoure.Enclsoure_class.Model_ID = Enclsoure.Enclsoure_class.Model_VA8200D;
                        I2connection.NumOfHDSlots = 8;
                        Prom_Enclosure_Serives.Log_File.FileLog("Model_ID=A8200D");
                    }
                    else {
                        // model is A8200 (2U8)
                        Enclsoure.Enclsoure_class.Model_ID = Enclsoure.Enclsoure_class.Model_VA8200;
                        I2connection.NumOfHDSlots = 8;
                        Prom_Enclosure_Serives.Log_File.FileLog("Model_ID=A8200");
                    }
                }
                else if (ReadSMB(PCH_Constants.PCH200_I2C_BP_DEV_ADDR_VA3120, 0xF4, 1, ref data_temp) == 0)
                {
                    // model is A8100 (1U4)
                    Enclsoure.Enclsoure_class.Model_ID = Enclsoure.Enclsoure_class.Model_VA8100;
                    I2connection.NumOfHDSlots = 4;
                    Prom_Enclosure_Serives.Log_File.FileLog("Model_ID=A8100");
                }
                else
                {
                    // model is A8020 (Tower) 
                    Enclsoure.Enclsoure_class.Model_ID = Enclsoure.Enclsoure_class.Model_VA8020;
                    I2connection.NumOfHDSlots = 2;
                    Prom_Enclosure_Serives.Log_File.FileLog("Model_ID=A8020");
                }
            }
        }

        public static byte ReadIOSp(uint address, uint offset)
        {
            return Ring0.ReadIoPort(offset + address);
        }

		public static int ReadSMB(uint address,uint offset, uint length,ref uint[] data)
        {
        int i=0;
            int ret = 0;
           for(i = 0;i < length; i++)
           {
                if (PCH200_smbus_check_ready() == -1)
                {
                    return -1;
                }
                /*fill up the data and tran*/
                Ring0.WriteIoPort(SMBHSTSTS, Convert.ToByte(0xBF));//BF is Complement of SMBHSTSTS_INUSE_STS
				//  it should be (SMBHSTSTS, ~Constants.SMBHSTSTS_INUSE_STS)

				Ring0.WriteIoPort(SMBHSTADD, Convert.ToByte((address & 0x7f) << 1 | PCH_Constants.I2C_SMBUS_READ));
				Ring0.WriteIoPort(SMBHSTCMD, Convert.ToByte(offset+i));
				
				ret = PCH200_smbus_transaction();
                Thread.Sleep(5);
                data[i] = Ring0.ReadIoPort(SMBHSTDAT0);

				//Console.WriteLine(" 0x{0:x} ", data);
		   }


            return ret;
        }

        public static int WriteSMB(uint address,uint offset, uint length,ref uint[] data)
        {
           int i=0;
           int ret = 0;
           for (i = 0;i < length; i++)
           {
                if (PCH200_smbus_check_ready() == -1)
                {
                    return -1;
                }
                /*fill up the data and tran*/
                Ring0.WriteIoPort(SMBHSTSTS, Convert.ToByte(0xBF));//BF is Complement of SMBHSTSTS_INUSE_STS
				//  it should be (SMBHSTSTS, ~Constants.SMBHSTSTS_INUSE_STS)

				Ring0.WriteIoPort(SMBHSTADD, Convert.ToByte((address & 0x7f) << 1 | PCH_Constants.I2C_SMBUS_WRITE));
				Ring0.WriteIoPort(SMBHSTCMD, Convert.ToByte(offset+i));
				Ring0.WriteIoPort(SMBHSTDAT0, Convert.ToByte(data[i]));

                ret = PCH200_smbus_transaction();
                Thread.Sleep(5);
		   }
            return ret;

        }
        private static int PCH200_smbus_transaction()
        {
            uint timeout = 0;
            uint hst_sts=0;
            uint hst_stat_check = 0;
            int result = 0;
            /*summit to PCI*/
            Ring0.WriteIoPort( SMBHSTCNT,Convert.ToByte(PCH_Constants.PCH_BYTE_DATA | PCH_Constants.PCH_START));

            while (timeout++ < PCH_Constants.MAX_BUSY_TIMEOUT)
            {

                hst_sts = Ring0.ReadIoPort(SMBHSTSTS);
                if ((hst_sts & PCH_Constants.SMBHSTSTS_INTR) == PCH_Constants.SMBHSTSTS_INTR)
                {
                    break;
                }
                else
                {
                    timeout++;
                    Thread.Sleep(1);
                    if (timeout == PCH_Constants.MAX_BUSY_TIMEOUT)
                    {
                        /* SMBus Kill Command */
                        Ring0.WriteIoPort(SMBHSTCNT, 0x02);
                        Ring0.WriteIoPort(SMBHSTSTS, 0xFF);
                    }
                }
            }

            hst_stat_check = hst_sts;

            /* If the SMBus is still busy, we give up */
            if (timeout >= PCH_Constants.MAX_BUSY_TIMEOUT)
            {
                result = -1;
                Console.WriteLine("SMBus Timeout (BUSY)!\n");
            }

            if ((hst_sts & PCH_Constants.SMBHSTSTS_FAILED)== PCH_Constants.SMBHSTSTS_FAILED)
            {
                result = -1;
                Console.WriteLine("Error: Failed bus transaction\n");
            }

            if ((hst_sts & PCH_Constants.SMBHSTSTS_BUS_ERR)== PCH_Constants.SMBHSTSTS_BUS_ERR)
            {
                result = -1;
                Console.WriteLine("Bus collision! SMBus may be locked until next hard reset. (sorry!)\n");
                /* Clock stops and slave is stuck in mid-transmission */
            }

            if ((hst_sts & PCH_Constants.SMBHSTSTS_DEV_ERR)== PCH_Constants.SMBHSTSTS_DEV_ERR)
            {
                result = -1;
                Console.WriteLine("Error: no response!\n");
            }

            /* Clear host status */
            hst_sts = Ring0.ReadIoPort(SMBHSTSTS);
            if ((hst_sts & 0x1f) != 0x00)
            {
               // ENC_OUTB(hst_sts, (unsigned short)SMBHSTSTS);
                Ring0.WriteIoPort(SMBHSTSTS, Convert.ToByte(hst_sts));
            }

            if (hst_stat_check == (PCH_Constants.SMBHSTSTS_INUSE_STS | PCH_Constants.SMBHSTSTS_BUS_ERR) ||
                hst_stat_check == (PCH_Constants.SMBHSTSTS_INUSE_STS | PCH_Constants.SMBHSTSTS_DEV_ERR))
            {
                PCH200HardSMBusReset();
                result = 1;
            }
            else if (hst_stat_check == (PCH_Constants.SMBHSTSTS_INUSE_STS | PCH_Constants.SMBHSTSTS_HOST_BUSY))
            {
                PCH200SoftSMBusReset();
                result = 1;
            }
            return result;
        }


        private static int PCH200_smbus_check_ready()
        {
            /* LOCAL VARIABLES DECLARATION
            */
            uint timeout = 0;
            uint hst_sts;   
            /* BODY
             */
            /* Check if SMBus semaphore has been released */
            /*while (timeout++ < PCH_Constants.MAX_INUSED_TIMEOUT*10)
            {
                hst_sts = Ring0.ReadIoPort(SMBHSTSTS);
                if ((hst_sts & PCH_Constants.SMBHSTSTS_INUSE_STS) == PCH_Constants.SMBHSTSTS_INUSE_STS)
                {
                    timeout++;
                    //Thread.Sleep(1);
                    if (timeout == PCH_Constants.MAX_INUSED_TIMEOUT)
                    {
                        Console.WriteLine("  ccc");
                        return -1;       
                    }
                }
                else
                    break;
            }*/

            timeout = 0;

            /* Check if SMBus is busy */
            while (timeout++ < PCH_Constants.MAX_BUSY_TIMEOUT)
            {
                //hst_sts = ENC_INB((unsigned short)SMBHSTSTS);
                hst_sts = Ring0.ReadIoPort(SMBHSTSTS);
                if ((hst_sts & PCH_Constants.SMBHSTSTS_HOST_BUSY) == PCH_Constants.SMBHSTSTS_HOST_BUSY)
                {
                    timeout++;
                    Thread.Sleep(3);
                    if (timeout == PCH_Constants.MAX_BUSY_TIMEOUT)
                    {
                        /* SMBus Kill Command */

                        Ring0.WriteIoPort(SMBHSTCNT, 0x02);
                        Ring0.WriteIoPort(SMBHSTSTS, 0xFF);
                        return -1;
                    }
                }
                else
                    return 0;
            }

            return 0;
        }

        private static int PCH200HardSMBusReset()
        {
             /* SMBus Kill Command */

            uint  tmpPCI_address = (PCH_Constants.PCH200_LPC_DEVICE_NUMBER << 3) | PCH_Constants.PCH200_LPC_FUNCTION_NUMBER;

            Ring0.WriteIoPort(SMBHSTCNT, (0x02 | 0x01));
            Ring0.WriteIoPort(SMBHSTSTS, (0xFF));
            /* Hare SMBus reset */
            Ring0.WritePciConfig(tmpPCI_address, 0xCF9, 0x0E);

            Thread.Sleep(5000);

            //nct7802y_chip_init();

            Console.WriteLine("Error: I2C reset done.\n");

            return 1;
        }

        private static int PCH200SoftSMBusReset()
        {
            //uint timeout, hst_sts;



            Ring0.WritePciConfig(PCI_address, PCH_Constants.PCH200_SMB_HOSTC, (PCH_Constants.PCH_SMBUS_ENABLE | PCH_Constants.PCH_SMBUS_SMI_EN));

            Ring0.WritePciConfig(PCI_address, PCH_Constants.PCH200_SMB_HOSTC, (PCH_Constants.PCH_SMBUS_ENABLE | PCH_Constants.PCH_SMBUS_SSRESET));
            
            Thread.Sleep(1000);

            //nct7802y_chip_init();

            Console.WriteLine("PCH200 SMBUS software reset!\n");

            return 1;
        }
    }
}


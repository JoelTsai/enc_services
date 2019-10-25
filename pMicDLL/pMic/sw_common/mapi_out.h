/*******************************************************************************
 * Filename    : mapi_out.h
 * Description : Output parameter header file of MAPI
 *               
 * Created on  : 05/24/2005
 * CVS Version : $Id: mapi_out.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2005
 * All Rights Reserved
 ******************************************************************************/
#define U256 256
#define U128 128 
#define U64 64 
#define U32 32

typedef struct output_bp_snapset
{
	struct output_bp_snapset * ptrnext;
	char vgname[U32];
	int upercnt;
	int maxsnap;
	float totalcap;
	int datacap;
	int snapcap;
	int snapsize;
}output_bp_snapset_t;

typedef struct output_hp_snapset
{
	output_bp_snapset_t * ptrfirst;
	int count;
}output_hp_snapset_t;

typedef struct output_bp_snaplist
{
	struct output_bp_snaplist * ptrnext;
	char vgname[U32];
	char lvname[U32];
	char spname[U32];
	int status;
	float spsize;
	int upercnt;
	int exportflag;
} output_bp_snaplist_t;

typedef struct output_hp_snaplist
{
	output_bp_snaplist_t * ptrfirst;
	int count;
} output_hp_snaplist_t;

typedef struct output_bp_getldname
{
	struct output_bp_getldname * ptrnext;
	char ldname[128];
}output_bp_getldname_t;

typedef struct output_hp_getldname
{
	output_bp_getldname_t * ptrfirst;
	int count;
}output_hp_getldname_t;

typedef struct output_bp_getptrinfo
{
	struct output_bp_getptrinfo * ptrnext;
	char maker[128];
	char model[128];
	char sn[128];
}output_bp_getptrinfo_t;

typedef struct output_hp_getptrinfo
{
	output_bp_getptrinfo_t * ptrfirst;
	int count;
}output_hp_getptrinfo_t;

typedef struct output_bp_getrsync
{
	struct output_bp_getrsync * ptrnext;
	char role[U32];
	char another[U32];
	char hostip[U32]; //for vessraid
}output_bp_getrsync_t;

typedef struct output_hp_getrsync
{
	output_bp_getrsync_t * ptrfirst;
	int count;
}output_hp_getrsync_t;



typedef struct output_bp_getdomain
{
	struct output_bp_getdomain * ptrnext;
	char dtype[6];
	char domain[U256];
	char kdc[U32];
}output_bp_getdomain_t;

typedef struct output_hp_getdomain
{
	output_bp_getdomain_t * ptrfirst;
	int count;
}output_hp_getdomain_t;


typedef struct output_bp_getsnaplv
{
	struct output_bp_getsnaplv * ptrnext;
	char lvname[64];
	char actlv[32];
	char snapstat[10];
	float cowsize;
	float alocrate;
	float chksize;
	char message[256];
}output_bp_getsnaplv_t;

typedef struct output_hp_getsnaplv
{
	output_bp_getsnaplv_t * ptrfirst;
	int count;
}output_hp_getsnaplv_t;

typedef struct output_bp_getvg
{
	struct output_bp_getvg * ptrnext;
	char vgname[32];
	char vgformat[6];
	char vgaccess[16];
	char vgstatus[16];
	int  maxlv;
	int  curlv;
	int  openlv;
	int  maxpv;
	int  curpv;
	int  actpv;
	float vgsize;
	float pesize;
	int  totalpe;
	int  allocpe;
	float allocpesize;
	int  freepe;
	float freepesize;
	char vguid[64];
	char message[256];
}output_bp_getvg_t;

typedef struct output_hp_getvg
{
	output_bp_getvg_t * ptrfirst;
	int count;
}output_hp_getvg_t;

typedef struct output_bp_getlv
{
	struct output_bp_getlv * ptrnext;
	char lvname[32];
	char vgname[32];
	char lvuid[64];
	int  lvtype;
	char lvwriteaccess[16];
	char lvstatus[10];
	float lvsize;
	int  curle;
	int  segm;
	char alloc[10];
	char message[256];
}output_bp_getlv_t;

typedef struct output_hp_getlv
{
        output_bp_getlv_t * ptrfirst;
        int count;
}output_hp_getlv_t;

typedef struct output_bp_getpv
{
	struct output_bp_getpv * ptrnext;
	char pvname[32];
	char vgname[32];
	float pvsize;
	char alloctable[4];
	int pesize;
	int totalpe;
	int freepe;
	int allocpe;
	char pvuid[64];
	char message[256];
}output_bp_getpv_t;

typedef struct output_hp_getpv
{
	output_bp_getpv_t * ptrfirst;
	int count;
}output_hp_getpv_t;

typedef struct output_bp_schedule
{
	struct output_bp_schedule * ptrnext;
	char scheduleitem[7];
	int type;
	int time1;
	int time2;
	int time3;
}output_bp_schedule_t;

typedef struct output_hp_schedule
{
	output_bp_schedule_t * ptrfirst;
	int count;
}output_hp_schedule_t;

typedef struct output_bp_timezone
{
	struct output_bp_timezone * ptrnext;
	char timezone[8];
	char dst[8];
}output_bp_timezone_t;

typedef struct output_hp_timezone
{
	output_bp_timezone_t * ptrfirst;
	int count;
}output_hp_timezone_t;

typedef struct output_bp_upsinfo
{
	struct output_bp_upsinfo * ptrnext;
	char manufact[U32];
	char product[U32];
	char sn[U32];
	char status[4];
	int  upstype;
	int  setvalue;
}output_bp_upsinfo_t;

typedef struct output_hp_upsinfo
{
	output_bp_upsinfo_t * ptrfirst;
	int count;
}output_hp_upsinfo_t;


typedef struct output_bp_ntpinfo
{
	struct output_bp_ntpinfo * ptrnext;
	char syncauto[4];
	char timeserver[U256];
	char syncdate[U32];
	char syncresult[U32];
}output_bp_ntpinfo_t;

typedef struct output_hp_ntpinfo
{
	output_bp_ntpinfo_t * ptrfirst;
	int count;
}output_hp_ntpinfo_t;


typedef struct output_bp_uilanguage
{
  	struct output_bp_uilanguage * ptrnext;
  	char language [16];
} output_bp_uilanguage_t;

typedef struct output_hp_uilanguage
{
  output_bp_uilanguage_t * ptrfirst;
  int count;
} output_hp_uilanguage_t;


/* System Infomation */

typedef struct output_bp_sysinfo
{
	struct  output_bp_sysinfo * ptrnext;
	char cpu[U32];
	char cpumhz[U32];
	char memsize[U32];
	char nic[64];
	char version[U32];
	char prdname[U32];
	char supraid[3];
	char basename[U32];
	char mac1[U32];
	char mac2[U32];
} output_bp_sysinfo_t;

typedef struct output_hp_sysinfo
{
	output_bp_sysinfo_t * ptrfirst;
	int count;    
} output_hp_sysinfo_t;

/* Network Information */

typedef struct output_bp_netinfo
{
	struct  output_bp_netinfo * ptrnext;
	char hostname[U32];
	char proto[8];
	char ip[U32];
	char netmask[U32];
	char gateway[U32];
	char dns1[U32];
	char dns2[U32];

	char lmode[U32];
	char lspeed[U32];
	char link[8];
	char mtu[8];     
	char wol[8];     
} output_bp_netinfo_t;

typedef struct output_hp_netinfo
{
	output_bp_netinfo_t * ptrfirst;
	int count;
     
} output_hp_netinfo_t;

/* Date */
   
typedef struct output_bp_date
{
	struct output_bp_date * ptrnext;
	char year[5];
	char mon[3];
	char day[3];
	char hour[3];
	char min[3];
	char sec[3];
} output_bp_date_t;

typedef struct output_hp_date
{
	output_bp_date_t * ptrfirst;
	int count;
} output_hp_date_t;

/* Enclosure Infomation */

typedef struct output_bp_encinfo
{
	struct  output_bp_encinfo * ptrnext;
	char temp1[8];
	char temp2[8];
	char fan1[8];
	char fan2[8];
	char fan3[8];
	char vcc[8];
	char vcc_max[8];
	char vcc_min[8];
	char v5[8];
	char v5_max[8];
	char v5_min[8];
	char v33[8];
	char v33_max[8];
	char v33_min[8];
	char v12[8];
	char v12_max[8];
	char v12_min[8];	
	char pwm[8];
	char pwmmode[8];
} output_bp_encinfo_t;

typedef struct output_hp_encinfo
{
	output_bp_encinfo_t * ptrfirst;
	int count;
     
} output_hp_encinfo_t;

/* Mail List */

typedef struct output_bp_maillist
{
	struct  output_bp_maillist * ptrnext;
	char mailaddr[64];
} output_bp_maillist_t;

typedef struct output_hp_maillist
{
	output_bp_maillist_t * ptrfirst;
	int count;
     
} output_hp_maillist_t;

/* User && Group */

typedef struct output_bp_usergroup
{
 	struct output_bp_usergroup * ptrnext;
 	char usergroup_name[U256];
} output_bp_usergroup_t;

typedef struct output_hp_usergroup
{
	output_bp_usergroup_t * ptrfirst;
	int count;
} output_hp_usergroup_t;

/* Quota */

typedef struct output_bp_quotainfo
{
      struct output_bp_quotainfo * ptrnext;
      char usergroup_name[U256];
      char mount_point[U32];
      int limit;
      int used;      
} output_bp_quotainfo_t;

typedef struct output_hp_quotainfo
{
	output_bp_quotainfo_t * ptrfirst;
	int count;
} output_hp_quotainfo_t;

/* Filesystem Information */

typedef struct output_bp_filesystem
{
      struct output_bp_filesystem * ptrnext;
      char mount_point[U32];
      char device[U32];
      float total;  
      float used;		
      float free;		
      int  usage;      
} output_bp_filesystem_t;

typedef struct output_hp_filesystem
{
	output_bp_filesystem_t * ptrfirst;
	int count;
} output_hp_filesystem_t;

/* Share Folder */

typedef struct output_bp_sharefolder
{
      struct output_bp_sharefolder * ptrnext; 
      char folder_name[U32];
      char mount_point[U32];
      int smb_flag;  //0:off ; 1:on
      int nfs_flag;
      int afp_flag;
      int ftp_flag;
} output_bp_sharefolder_t;

typedef struct output_hp_sharefolder
{
	output_bp_sharefolder_t * ptrfirst;
	int count;
} output_hp_sharefolder_t;

/* Get All Service Status Infomation */

typedef struct output_bp_protocol
{
   	struct output_bp_protocol * ptrnext;
   	char protocol[8];
   	char version[U32];
   	char enable[8];
   	char status[8];
   	char descp[U32];
   	char mport[8];
} output_bp_protocol_t;

typedef struct output_hp_protocol
{
	output_bp_protocol_t * ptrfirst;
	int count;
} output_hp_protocol_t;

/* Get NFS Sharing IP Address */

typedef struct output_bp_nfsshare
{
	struct output_bp_nfsshare * ptrnext;
	char ip[U32];
} output_bp_nfsshare_t;

typedef struct output_hp_nfsshare
{
	output_bp_nfsshare_t  * ptrfirst;
	int count;
} output_hp_nfsshare_t;

/* Event Log */

typedef struct output_bp_eventlog
{
	struct output_bp_eventlog * ptrnext;
	char date[U32];
	char level[U32];
	char message[U256];
} output_bp_eventlog_t;

typedef struct output_hp_eventlog
{
	output_bp_eventlog_t  * ptrfirst;
	int count;
} output_hp_eventlog_t;

/* Get Samba Config Information */

typedef struct output_bp_smbconfig	
{
 	struct output_bp_smbconfig * ptrnext;
 	char codepage[8];
 	char netbiosname[U32];
 	char domain[U256];
 	char description[U256];
} output_bp_smbconfig_t;

typedef struct output_hp_smbconfig	
{
	output_bp_smbconfig_t * ptrfirst;
	int count;
} output_hp_smbconfig_t;

/* Performance */

typedef struct output_bp_performance	
{
 	struct output_bp_performance * ptrnext;
	int cpu_usage;
	int mem_total;
	int mem_used;
	long eth0_in;
	long eth0_out;
	long eth1_in;
	long eth1_out;
} output_bp_performance_t;

typedef struct output_hp_performance	
{
	output_bp_performance_t * ptrfirst;
	int count;
} output_hp_performance_t;

/* Get Group Members */

typedef struct output_bp_groupmember
{
        struct output_bp_groupmember * ptrnext;
        char member[U256];
} output_bp_groupmember_t;

typedef struct output_hp_groupmember
{
        output_bp_groupmember_t * ptrfirst;
        int count;
} output_hp_groupmember_t;

/* Get Permission */ 

typedef struct output_bp_permission
{
        struct output_bp_permission * ptrnext;
        char usergroup_name[U256];
        int permission; 				// 0:Deny; 1:Read-Only ;2:Read-Write
} output_bp_permission_t;

typedef struct output_hp_permission
{
        output_bp_permission_t * ptrfirst;
        int count;
} output_hp_permission_t;

typedef struct output_bp_usbdisk
{
        struct output_bp_usbdisk * ptrnext;
        char umaker[U128];
        char umodel[U128];
        char usn[U128];
        char dvendor[U128];
        char dmodel[U128];
        char dfwver[U128];
	float dsize;
}output_bp_usbdisk_t;

typedef struct output_hp_usbdisk
{
	output_bp_usbdisk_t * ptrfirst;
	int count;
} output_hp_usbdisk_t;

typedef struct output_bp_onetouch
{
        struct output_bp_onetouch * ptrnext;
        char service[8];
        char type[8];
        char target[U32];
        char clientip[U32];
} output_bp_onetouch_t;

typedef struct output_hp_onetouch
{
	      output_bp_onetouch_t * ptrfirst;
	      int count;
} output_hp_onetouch_t;

/* Mount Point Information */

typedef struct output_bp_mountinfo
{
      struct output_bp_mountinfo * ptrnext;
      char mount_point[U32];
      int ldid;      
      char ldname[U32];
      char device[U32];
      char path[U64];
} output_bp_mountinfo_t;

typedef struct output_hp_mountinfo
{
	output_bp_mountinfo_t * ptrfirst;
	int count;
} output_hp_mountinfo_t;

typedef struct output_bp_smtp
{
	struct output_bp_smtp * ptrnext;
	char service[5];
	char smtp[U256];
	char from[U256];
	char auth[5];
	char user[U256];
	char passwd[32];
	char port[8];
} output_bp_smtp_t;

typedef struct output_hp_smtp
{
	output_bp_smtp_t * ptrfirst;
	int count;
} output_hp_smtp_t;

typedef struct output_bp_ddns
{
	struct output_bp_ddns * ptrnext;
	char domain[U256];
	char user[U256];
	char passwd[32];
} output_bp_ddns_t;

typedef struct output_hp_ddns
{
	output_bp_ddns_t * ptrfirst;
	int count;
} output_hp_ddns_t;

typedef struct output_bp_ftp
{
	struct output_bp_ftp * ptrnext;
	char remote_code[8];
	char port[8];
  char pass_sport[8];
  char pass_eport[8];
  char ssl[8];
} output_bp_ftp_t;

typedef struct output_hp_ftp
{
	output_bp_ftp_t * ptrfirst;
	int count;
} output_hp_ftp_t;

typedef struct output_bp_onlineuser
{
	struct output_bp_onlineuser * ptrnext;
	char machine[U256];
	char ip[U32];
	char user[U256];
	char group[U256];
	char time[U64];
} output_bp_onlineuser_t;

typedef struct output_hp_onlineuser
{
	output_bp_onlineuser_t * ptrfirst;
	int count;
} output_hp_onlineuser_t;

typedef struct output_bp_filemgt
{
	struct output_bp_filemgt * ptrnext;
	char folder_c[16];
	char file_c[16];
	char faction[U256];
	char findex[16];
	char fname[U256];
	char ftype[8];
	char fsize[16];
	char ftime[U32];
}output_bp_filemgt_t;

typedef struct output_hp_filemgt
{
	output_bp_filemgt_t * ptrfirst;
	int count;
}output_hp_filemgt_t;

typedef struct output_bp_ipinfo
{
	struct output_bp_ipinfo * ptrnext;
	char id[16];
	char ip[U32];
	char mac[U32];
}output_bp_ipinfo_t;

typedef struct output_hp_ipinfo
{
	output_bp_ipinfo_t * ptrfirst;
	int count;
}output_hp_ipinfo_t;

/******************************************************************************
 * Filename    : mapi_in.h
 * Description : Input parameter header file of MAPI
 *               
 * Created on  : 05/24/2005
 * CVS Version : $Id: mapi_in.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2005
 * All Rights Reserved
 ******************************************************************************/
#define U256 256
#define U32 32 
#define U6 6

typedef struct input_setldname
{
	char ldname[U32];
} input_setldname_t;


typedef struct input_snapshot
{
	char vgname[U32];
	char lvname[U32];
	int upercnt;
	int maxsnap;
}input_snapshot_t;

typedef struct input_setrsync
{
	char role[U32];
	char another[U32];
	char hostip[U32]; //add for vessraid
}input_setrsync_t;

typedef struct input_setdomain
{
	char dtype[6];
	char domainname[U256];
	char kdc[U32];
	char username[U256];
	char password[U256];
}input_setdomain_t;

typedef struct input_setsnaplv
{
	char vgname[U32];
	char spname[U32];
	float spsize;
	char lvname[U32];
	char fullname[128];
	char action[U32];	
}input_setsnaplv_t;

typedef struct input_setvg
{
	char vgname[U32];
	int  pvnum;
	char pvname[U32];
}input_setvg_t;

typedef struct input_setlv
{
	char lvname[U32];
	float lvsize;
	char vgname[U32];
	char fullname[128];
}input_setlv_t;

typedef struct input_setpv
{
	char pvname[U32];
}input_setpv_t;

typedef struct input_schedule
{
	char scheduleitem[8];
	int type;
	int time1;
	int time2;
	int time3;
}input_schedule_t;

typedef struct input_ntp
{
	char syncauto[5];
	char timeserver[U256];
}input_ntp_t;

typedef struct input_ups
{
	int upstype;
	int setvalue;
}input_ups_t;


typedef struct input_timezone
{
	char zone[8];
	char dst[8];
}input_timezone_t;

typedef struct input_uilanguage
{
	char language[16];       
} input_uilanguage_t;
 
 
typedef struct input_log
{
	char hostname[U32];
	char facility[U32];
	char level[U32];
	char message[128];
} input_log_t;


 typedef struct input_usergroup
{
	char username[U256];
	char groupname[U256];
	char password[U256];
} input_usergroup_t;

typedef struct input_sharefolder
{
        char foldername[U32];
        char mount_point[U32];
        char protocol[8];
} input_sharefolder_t;


typedef struct input_date{
		int year;
		int mon;
		int day;
		int hour;
		int min;
		int sec;       
} input_date_t;

typedef struct input_maillist
{
	char mailaddr[64];
}input_maillist_t;

typedef struct input_network
{
        char hostname[U32];
        char proto[16];
        char ip[U32];
        char netmask[U32];
        char gateway[U32];
        char dns1[U32];
        char dns2[U32];
        char mtu[8];
} input_network_t;

typedef struct input_quota{
        char usergroup_name[U256];
        char mount_point[U32];
        int  limit;
} input_quota_t;


//=====================================================

typedef struct inparm
{
	int num;
	int index;
}inparm_t;

typedef struct bodycell
{
 	struct bodycell * ptr;
 	char version[U32];
 	int  capacity;
  	
}bodycell_t;

typedef struct headcell
{
	bodycell_t * ptrfirst;
	int count;
     
}headcell_t;

typedef struct input_sharing
{
        char foldername[U32];
        char usergroup_name[U256];
        int permission; //0-Deny;1-Readonly;2-Readwrite;
        char ip[U32];
	      char mount_point[U32];
}input_sharing_t;

typedef struct input_protoctl
{
	int startstop;
	char fstype[8];
	char codepage[8];
	char domain[U256];
	char description[U256];
}input_protoctl_t;
typedef struct input_fsformat{
   	int level;
	
}input_fsformat_t;

typedef struct input_upgrade
{
	char mount_point[U32];
        char foldername[U32];
        char upgrade_file[U256];
} input_upgrade_t;


typedef struct input_smbconfig
{
  char codepage[8];
  char workgroup[U256];
  char description[U256];
} input_smbconfig_t;

typedef struct input_onetouch
{
  char service[8];
  char type[8];
  char clientip[U32];
} input_onetouch_t;

typedef struct input_usbhd
{
  char fstype[16];
} input_usbhd_t;

typedef struct input_raid
{
  char ldname[U32];
  int  ldid;
  char mount_point[U256];
  char action[U6];
} input_raid_t;

typedef struct input_auth
{
  char authmode[8];
} input_auth_t;

typedef struct input_smtp
{
	char service[5];
	char smtp[U256];
	char from[U256];
	char auth[5];
	char user[U256];
	char passwd[U256];
	char port[8];
} input_smtp_t;

typedef struct input_ddns
{
	char domain[U256];
	char user[U256];
	char passwd[U256];
} input_ddns_t;

typedef struct input_ftp
{
	char remote_code[8];
	char port[8];
  char pass_sport[8];
  char pass_eport[8];
} input_ftp_t;

typedef struct input_command
{
	char command[U256];
} input_command_t;

typedef struct input_event //add for VessRAID
{
	unsigned short classid;
	unsigned short eventid;
	char extradata[U32];
} input_event_t;


/* netstart.c - netstart */

#include <xinu.h>

/*------------------------------------------------------------------------
 * netstart  -  Initialize network and run DHCP to get an IP address
 *------------------------------------------------------------------------
 */

void	netstart (char *bbb_ipaddr, char *bbb_router) {
  uint32 ipaddr;			/* IP address			*/
  uint32 router;			/* Router			*/
  uint32 mask;			        /* Subnet Mask			*/
  
  /* Initialize the network stack */
  
  kprintf("...initializing network stack\n");
  net_init();
  
  dot2ip(bbb_ipaddr,&ipaddr);
  NetData.ipucast = ipaddr;
  
  kprintf("\nIP address is %d.%d.%d.%d   (0x%08x)\n\r",
	  (ipaddr>>24)&0xff, (ipaddr>>16)&0xff, (ipaddr>>8)&0xff,
	  ipaddr&0xff,ipaddr);
  
  dot2ip("255.255.255.0",&mask);
  NetData.ipmask = 0xFFFFFF00;
  dot2ip(bbb_router,&router);
  NetData.iprouter = router;
  NetData.ipprefix = NetData.ipucast & NetData.ipmask;
  NetData.ipbcast = NetData.ipprefix | ~NetData.ipmask;
  NetData.ipvalid = TRUE;
  
  kprintf("Subnet mask is %d.%d.%d.%d and router is %d.%d.%d.%d\n\r",
	  (NetData.ipmask>>24)&0xff, (NetData.ipmask>>16)&0xff,
	  (NetData.ipmask>> 8)&0xff,  NetData.ipmask&0xff,
	  (NetData.iprouter>>24)&0xff, (NetData.iprouter>>16)&0xff,
	  (NetData.iprouter>> 8)&0xff, NetData.iprouter&0xff);
  
  return;
}

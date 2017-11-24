#include<stdio.h>
#include<stdlib.h>
struct packet_s
{
char d_mac[12];
char s_mac[12];
int vlan;
int ethertype;
};
void print_packet(struct packet_s packet_t);
int main()
{
struct packet_s packet_t;
printf(" Packet builder \n");
printf("-----------------\n");

printf ("Destination Mac : ");
scanf("%s",packet_t.d_mac);
//gets(packet_t.d_mac);

printf("\n");

printf("Source Mac      : ");
scanf("%s",packet_t.s_mac);

printf("\n");

printf(" Vlan		: ");
scanf("%d",&packet_t.vlan);

printf("\n");

printf("Ethertype	: ");
scanf("%d",&packet_t.ethertype);

printf(" Calling the function ");
print_packet(packet_t);
}
void print_packet(struct packet_s packet_t)
{
printf( "\n the dest mac is ");
printf("%s",packet_t.d_mac);
}

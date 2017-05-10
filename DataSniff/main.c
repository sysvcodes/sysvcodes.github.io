
/*
** DataSniff V1.0
** Coded by SysV
** https://github.com/sysvcodes
*/

/* Configurações da janela */
#define TITLE         "DataSniff 1.0 - By SysV"
#define WIDTH         1300
#define HEIGHT        700
#define DEFAULT_RULE  "true"

#pragma comment(lib, "Shlwapi.lib")

#include <winsock2.h>
#include <Windows.h>
#include <Shlwapi.h>
#include <Commctrl.h>
#include <Winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define HM_LIST_VIEW 16700
#define HM_EDIT_CONTENT 17893
#define HM_BTN_START_WINDIVERT 18023
#define HM_BTN_STOP_WINDIVERT 19912

#define IDI_SHIELD MAKEINTRESOURCE(32518)
#define CDRF_DODEFAULT 0x00000000
#define CDDS_PREPAINT 1
#define CDRF_NOTIFYITEMDRAW 0x20 
#define CDDS_ITEMPREPAINT 65537
#define CDRF_NEWFONT 0x02
#define CDDS_SUBITEM 0x20000

#define INT8 int8_t
#define UINT8 uint8_t
#define INT16 int16_t
#define UINT16 uint16_t
#define INT32 int32_t
#define UINT32 uint32_t
#define INT64 int64_t
#define UINT64 uint64_t
#define WINDIVERT_HELPER_NO_REPLACE 2048

#define WINDIVERT_IPHDR_GET_FRAGOFF(hdr)                    \
    (((hdr)->FragOff0) & 0xFF1F)
#define WINDIVERT_IPHDR_GET_MF(hdr)                         \
    ((((hdr)->FragOff0) & 0x0020) != 0)
#define WINDIVERT_IPHDR_GET_DF(hdr)                         \
    ((((hdr)->FragOff0) & 0x0040) != 0)
#define WINDIVERT_IPHDR_GET_RESERVED(hdr)                   \
    ((((hdr)->FragOff0) & 0x0080) != 0)

#define WINDIVERT_IPHDR_SET_FRAGOFF(hdr, val)               \
    do                                                      \
    {                                                       \
        (hdr)->FragOff0 = (((hdr)->FragOff0) & 0x00E0) |    \
            ((val) & 0xFF1F);                               \
    }                                                       \
    while (FALSE)
#define WINDIVERT_IPHDR_SET_MF(hdr, val)                    \
    do                                                      \
    {                                                       \
        (hdr)->FragOff0 = (((hdr)->FragOff0) & 0xFFDF) |    \
            (((val) & 0x0001) << 5);                        \
    }                                                       \
    while (FALSE)
#define WINDIVERT_IPHDR_SET_DF(hdr, val)                    \
    do                                                      \
    {                                                       \
        (hdr)->FragOff0 = (((hdr)->FragOff0) & 0xFFBF) |    \
            (((val) & 0x0001) << 6);                        \
    }                                                       \
    while (FALSE)
#define WINDIVERT_IPHDR_SET_RESERVED(hdr, val)              \
    do                                                      \
    {                                                       \
        (hdr)->FragOff0 = (((hdr)->FragOff0) & 0xFF7F) |    \
            (((val) & 0x0001) << 7);                        \
    }                                                       \
    while (FALSE)

#define WINDIVERT_IPV6HDR_GET_TRAFFICCLASS(hdr)             \
    ((((hdr)->TrafficClass0) << 4) | ((hdr)->TrafficClass1))
#define WINDIVERT_IPV6HDR_GET_FLOWLABEL(hdr)                \
    ((((UINT32)(hdr)->FlowLabel0) << 16) | ((UINT32)(hdr)->FlowLabel1))

#define WINDIVERT_IPV6HDR_SET_TRAFFICCLASS(hdr, val)        \
    do                                                      \
    {                                                       \
        (hdr)->TrafficClass0 = ((UINT8)(val) >> 4);         \
        (hdr)->TrafficClass1 = (UINT8)(val);                \
    }                                                       \
    while (FALSE)
#define WINDIVERT_IPV6HDR_SET_FLOWLABEL(hdr, val)           \
    do                                                      \
    {                                                       \
        (hdr)->FlowLabel0 = (UINT8)((val) >> 16);           \
        (hdr)->FlowLabel1 = (UINT16)(val);                  \
    }                                                       \
    while (FALSE)

typedef enum 
{
  WINDIVERT_LAYER_NETWORK = 0,
  WINDIVERT_LAYER_NETWORK_FORWARD = 1
} WINDIVERT_LAYER, *PWINDIVERT_LAYER;

typedef enum
{
    WINDIVERT_PARAM_QUEUE_LEN  = 0,
    WINDIVERT_PARAM_QUEUE_TIME = 1
} WINDIVERT_PARAM, *PWINDIVERT_PARAM;

typedef struct
{
  UINT32 IfIdx;
  UINT32 SubIfIdx;
  UINT8  Direction;
} WINDIVERT_ADDRESS, *PWINDIVERT_ADDRESS;

typedef struct
{
  UINT8  HdrLength:4;
  UINT8  Version:4;
  UINT8  TOS;
  UINT16 Length;
  UINT16 Id;
  UINT16 FragOff0;
  UINT8  TTL;
  UINT8  Protocol;
  UINT16 Checksum;
  UINT32 SrcAddr;
  UINT32 DstAddr;
} WINDIVERT_IPHDR, *PWINDIVERT_IPHDR;

typedef struct
{
  UINT8  TrafficClass0:4;
  UINT8  Version:4;
  UINT8  FlowLabel0:4;
  UINT8  TrafficClass1:4;
  UINT16 FlowLabel1;
  UINT16 Length;
  UINT8  NextHdr;
  UINT8  HopLimit;
  UINT32 SrcAddr[4];
  UINT32 DstAddr[4];
} WINDIVERT_IPV6HDR, *PWINDIVERT_IPV6HDR;

typedef struct
{
  UINT8  Type;
  UINT8  Code;
  UINT16 Checksum;
  UINT32 Body;
} WINDIVERT_ICMPHDR, *PWINDIVERT_ICMPHDR;

typedef struct
{
  UINT8  Type;
  UINT8  Code;
  UINT16 Checksum;
  UINT32 Body;
} WINDIVERT_ICMPV6HDR, *PWINDIVERT_ICMPV6HDR;

typedef struct
{
  UINT16 SrcPort;
  UINT16 DstPort;
  UINT32 SeqNum;
  UINT32 AckNum;
  UINT16 Reserved1:4;
  UINT16 HdrLength:4;
  UINT16 Fin:1;
  UINT16 Syn:1;
  UINT16 Rst:1;
  UINT16 Psh:1;
  UINT16 Ack:1;
  UINT16 Urg:1;
  UINT16 Reserved2:2;
  UINT16 Window;
  UINT16 Checksum;
  UINT16 UrgPtr;
} WINDIVERT_TCPHDR, *PWINDIVERT_TCPHDR;

typedef struct
{
  UINT16 SrcPort;
  UINT16 DstPort;
  UINT16 Length;
  UINT16 Checksum;
} WINDIVERT_UDPHDR, *PWINDIVERT_UDPHDR;

typedef struct
{
  WINDIVERT_IPHDR ip;
  WINDIVERT_TCPHDR tcp;
} TCPPACKET, *PTCPPACKET;

typedef struct
{
  WINDIVERT_IPV6HDR ipv6;
  WINDIVERT_TCPHDR tcp;
} TCPV6PACKET, *PTCPV6PACKET;

typedef struct
{
  WINDIVERT_IPHDR ip;
  WINDIVERT_ICMPHDR icmp;
  UINT8 data[];
} ICMPPACKET, *PICMPPACKET;

typedef struct
{
  WINDIVERT_IPV6HDR ipv6;
  WINDIVERT_ICMPV6HDR icmpv6;
  UINT8 data[];
} ICMPV6PACKET, *PICMPV6PACKET;

typedef struct
{
  WINDIVERT_IPHDR  ip;
  WINDIVERT_TCPHDR tcp;
} PACKET, *PPACKET;

typedef struct 
{
  PACKET header;
  UINT8 data[];
} DATAPACKET, *PDATAPACKET;

typedef HANDLE (*WinDivertOpenType)(const char *, WINDIVERT_LAYER, INT16, UINT64);
typedef BOOL (*WinDivertRecvType)(HANDLE, PVOID, UINT, PWINDIVERT_ADDRESS, UINT *);
typedef UINT (*WinDivertHelperCalcChecksumsType)(PVOID, UINT, UINT64);
typedef BOOL (*WinDivertSendType)(HANDLE, PVOID, UINT, PWINDIVERT_ADDRESS, UINT *);
typedef BOOL (*WinDivertHelperParsePacketType)(void *, UINT packetLen, PWINDIVERT_IPHDR *, 
  PWINDIVERT_IPV6HDR *, PWINDIVERT_ICMPHDR *, PWINDIVERT_ICMPV6HDR *, PWINDIVERT_TCPHDR *, 
  PWINDIVERT_UDPHDR *, PVOID *,  UINT *);
typedef BOOL (*WinDivertSetParamType)(HANDLE, WINDIVERT_PARAM, UINT64);
    
WinDivertOpenType WinDivertOpen;
WinDivertRecvType WinDivertRecv;
WinDivertHelperCalcChecksumsType WinDivertHelperCalcChecksums;
WinDivertSendType WinDivertSend;
WinDivertHelperParsePacketType WinDivertHelperParsePacket;
WinDivertSetParamType WinDivertSetParam;

const char w_class_name[] = "DSClass";
HWND listview, content_window, windivert_edit_control;
HWND payload_content, packet_content;
HANDLE g_mutex;
int current_packet_index = 0;
int stop_windivert_process = 0;
char global_filter [256];

LRESULT CALLBACK window_callback (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int insert_listview_item (
  HWND listview, int item, char *item_text, char *sub1, char *sub2, char *sub3, char *sub4, char *sub5);
HWND create_list_view (HWND parent);
int init_list_view (HWND listview);
void DS_control (void *lparam);
void windivert_control (char *filter);

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR line, int show)
{
  WNDCLASSEXA wnd;
  HWND window, hwnd_lv;
  MSG msg;
  int result = 0;
  
  g_mutex = CreateMutex(NULL, FALSE, NULL);
  CreateDirectoryA("log", NULL);
  windivert_control(DEFAULT_RULE);
  
  /* Cria janela... */
  wnd.cbSize          = sizeof(WNDCLASSEX);
  wnd.style           = CS_HREDRAW | CS_VREDRAW;
  wnd.lpfnWndProc     = (WNDPROC) window_callback;
  wnd.cbClsExtra      = 0;
  wnd.cbWndExtra      = 0;
  wnd.hInstance       = instance;
  wnd.hIcon           = (HICON) LoadImage(NULL, "icon_128x128.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
  wnd.hIconSm         = (HICON) LoadImage(NULL, "icon_128x128.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
  wnd.hCursor         = LoadCursor(NULL, IDC_ARROW);
  wnd.hbrBackground   = (HBRUSH)GetStockObject(DKGRAY_BRUSH); /* (HBRUSH)(COLOR_WINDOW+1); */
  wnd.lpszClassName   = w_class_name;
  wnd.lpszMenuName    = NULL;
  
  if (!RegisterClassExA(&wnd)) {
    MessageBoxA(0, "Error register class!", "Error!", MB_OK | MB_ICONERROR);
    return 1;
  }
  
  /* Janela principal. */
  window = CreateWindowExA(0, w_class_name, TITLE, WS_BORDER | WS_CAPTION 
    /*| WS_MAXIMIZEBOX*/ | WS_MINIMIZEBOX | WS_SYSMENU,
    (GetSystemMetrics(SM_CXSCREEN) - WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) / 2,
    WIDTH, HEIGHT, HWND_DESKTOP, NULL, instance, NULL);
  
  if (!window) {
    MessageBoxA(0, "Create window!", "Error!", MB_OK | MB_ICONERROR);
    return 1;
  }
  
  /* Listview. */
  HFONT font = CreateFontA(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, 
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
  
  hwnd_lv = CreateWindowExA(0, w_class_name, NULL, WS_CHILD | WS_VISIBLE,
      0, 30, WIDTH-8, (HEIGHT / 3) - 30, window, (HMENU) 1, (HINSTANCE) instance, NULL);
  
  if (hwnd_lv) {
    if ((listview = create_list_view(hwnd_lv))) {
      if ((result = init_list_view(listview)) == FALSE) {
        MessageBoxA(NULL, "Listview error.", "Error!", MB_OK | MB_ICONERROR);
        ExitProcess(0);
      } else {
        SendMessage(listview, (0x1000+54), 0, 32);
        
        content_window = CreateWindowA("EDIT", "", 
          WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
          ES_AUTOVSCROLL | ES_MULTILINE, 0, 
          (HEIGHT / 3) + 1, (WIDTH-8)/4, ((HEIGHT / 3) * 2) - 25,
          window, (HMENU) HM_EDIT_CONTENT, instance, NULL );
          
        packet_content = CreateWindowA("EDIT", "", 
          WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
          ES_AUTOVSCROLL | ES_MULTILINE, (WIDTH-8)/4, 
          (HEIGHT / 3) + 1, (WIDTH-8)/4, ((HEIGHT / 3) * 2) - 25,
          window, (HMENU) HM_EDIT_CONTENT, instance, NULL );
          
        payload_content = CreateWindowA("EDIT", "", 
          WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
          ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL, ((WIDTH-8)/4)*2, 
          (HEIGHT / 3) + 1, ((WIDTH-8)/4)*2, ((HEIGHT / 3) * 2) - 25,
          window, (HMENU) HM_EDIT_CONTENT, instance, NULL );
         
        SendMessageA(content_window, WM_SETFONT, (WPARAM) font, TRUE);
        SendMessageA(packet_content, WM_SETFONT, (WPARAM) font, TRUE);
        SendMessageA(payload_content, WM_SETFONT, (WPARAM) font, TRUE);
      }
    }
  }
  
  /* Controles. */
  #define offsetlv 680
  
  windivert_edit_control = CreateWindowA("EDIT", "true", 
    WS_CHILD | /*WS_VISIBLE |*/ ES_LEFT | ES_WANTRETURN | ES_AUTOHSCROLL, 
    5, 5, 500, 20,
    window, (HMENU) HM_EDIT_CONTENT, instance, NULL );
  
  SendMessageA(windivert_edit_control, EM_SETLIMITTEXT, (WPARAM) 0x7FFFFFFE, 0);
  SendMessageA(windivert_edit_control, WM_SETFONT, (WPARAM) font, TRUE);
  
  HWND button_start_windivert = CreateWindowA( 
    "BUTTON", "START",
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
    510+offsetlv, 5, 50, 20,
    window, (HMENU) HM_BTN_START_WINDIVERT, instance, NULL);
  
  HWND button_stop_windivert = CreateWindowA( 
    "BUTTON", "STOP",
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
    560+offsetlv, 5, 50, 20,
    window, (HMENU) HM_BTN_STOP_WINDIVERT, instance, NULL);
  
  /* ShowWindow(window, SW_MAXIMIZE); */
  ShowWindow(window, SW_SHOWNORMAL);
  UpdateWindow(window);
  
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return (int) msg.wParam;
}

/* Callback... */
LRESULT CALLBACK window_callback (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  FILE *fp = NULL;
  HWND hwnd_lv, hwnd_df;
  int current_item = 0, current_size = 0, total_size = 0, size = 0;
  char temp [256], line [256], *content = NULL;
  
  switch (msg)
  {
  case WM_CREATE: break;
  case WM_CLOSE: 
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(WM_QUIT);
    break;
  
  case WM_COMMAND:
    switch(LOWORD(wparam))
    {
    case HM_BTN_START_WINDIVERT:
      {
        /*char *filter = NULL;
        if ((filter = realloc(filter, 256)) != NULL) {
          memset(filter, '\0', 256);
          size = SendMessage(windivert_edit_control, WM_GETTEXTLENGTH, 0, 0);
          SendMessage(windivert_edit_control, WM_GETTEXT, (WPARAM) size+1, (LPARAM) filter);
          filter[size+1] = '\0';
          windivert_control(filter);
          filter = realloc(filter, 0);
        }*/
        stop_windivert_process = 0;
      }
      break;
    case HM_BTN_STOP_WINDIVERT:
      stop_windivert_process = 1; /* Flag sinalizada para finalizar thread. */
      break;
    }
    break;
  
  case WM_NOTIFY:
		switch(LOWORD(wparam))
		{
		case HM_LIST_VIEW:
      if(((LPNMHDR)lparam)->code == LVN_ITEMCHANGED)
			{
        current_item = (int) SendMessage(listview, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
				if(current_item == -1)
					return FALSE;
        
        memset(line, '\0', 256);
        memset(temp, '\0', 256);
        sprintf(temp, "log\\%d.log", current_item);
        
        if ((fp = fopen(temp, "r")) != NULL) {
          while (fgets(line, 256, fp)) {
            current_size = strlen(line);
            if ((content = realloc(content, current_size + total_size)) != NULL) {
              memcpy(&content[total_size], line, current_size);
              total_size += current_size;
            }
            memset(line, '\0', 256);
          }
          fclose(fp);
        }
        
        if ((fp = fopen(temp, "r")) != NULL) {
          while (fgets(line, 256, fp)) {
            current_size = strlen(line);
            if ((content = realloc(content, current_size + total_size)) != NULL) {
              memcpy(&content[total_size], line, current_size);
              total_size += current_size;
            }
            memset(line, '\0', 256);
          }
          fclose(fp);
        }
        
        if (total_size) {
          char *ip_packet = strstr(content, "\r\n\r\n");
          if (ip_packet) {
            ip_packet += strlen("\r\n\r\n");
             if ((ip_packet = strstr(ip_packet, "\r\n\r\n"))) {
              *ip_packet = '\0';
              SetWindowTextA(content_window, content);
              ip_packet += strlen("\r\n\r\n");
              char *ip_ptr = strstr(ip_packet, "\r\n\r\n");
              *ip_ptr = '\0';
              SetWindowTextA(packet_content, ip_packet);
              ip_ptr += strlen("\r\n\r\n");
              if (ip_ptr) {
                ip_packet = strstr(ip_ptr, "\r\n\r\n");
                ip_packet += strlen("\r\n\r\n");
                ip_packet = strstr(ip_packet, "\r\n\r\n");
                *ip_packet = '\0';
                SetWindowTextA(payload_content, ip_ptr);
              }
             }
          }
          content = realloc(content, 0);
        }
        
      }
      break;
    }
    
    if(((LPNMHDR)lparam)->code == NM_CUSTOMDRAW)
    {
      LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW) lparam;
      switch(lplvcd->nmcd.dwDrawStage)
      {
        case CDDS_PREPAINT:
          return CDRF_NOTIFYITEMDRAW;
        break;
        case CDDS_ITEMPREPAINT:
          if (((int)lplvcd->nmcd.dwItemSpec % 2) == 0) {
            lplvcd->clrText   = RGB(0,0,0);
            lplvcd->clrTextBk = RGB(102, 255, 102);
          } else {
            lplvcd->clrText   = RGB(0,0,255);
            lplvcd->clrTextBk = RGB(0, 255, 204);
          }
          return CDRF_NEWFONT;
        break;
        case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
          return CDRF_NEWFONT;    
        break;
      }
      return TRUE;
    }
    break;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

/* Inicializa biblioteca. */
void windivert_control (char *filter)
{
  /* Prepara biblioteca. */
  LoadLibraryA("WinDivert.dll");
	
	WinDivertOpen = (WinDivertOpenType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertOpen");
	WinDivertRecv = (WinDivertRecvType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertRecv");
	WinDivertHelperCalcChecksums = (WinDivertHelperCalcChecksumsType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertHelperCalcChecksums");
	WinDivertSend = (WinDivertSendType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertSend");
	WinDivertHelperParsePacket = (WinDivertHelperParsePacketType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertHelperParsePacket");
	WinDivertSetParam = (WinDivertSetParamType) GetProcAddress(GetModuleHandleA("WinDivert.dll"), "WinDivertSetParam");
  
  HANDLE thread;
  HANDLE handle = WinDivertOpen(filter, 0, 0, 1);
  
  if (handle == INVALID_HANDLE_VALUE)
  {
    MessageBoxA(NULL, "Error load WinDivert DLL.", "Error!", MB_OK | MB_ICONERROR);
    ExitProcess(0);
  }
  
  if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_LEN, 8192))
  {
    MessageBoxA(NULL, "Failed to set packet queue length.", "Error!", MB_OK | MB_ICONERROR);
    ExitProcess(0);
  }
  
  if (!WinDivertSetParam(handle, WINDIVERT_PARAM_QUEUE_TIME, 2048))
  {
    MessageBoxA(NULL, "Failed to set packet queue time.", "Error!", MB_OK | MB_ICONERROR);
    ExitProcess(0);
  }
  
  // DS_control(handle);
  thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) DS_control, (PVOID) handle, 0, NULL);
}

/* Insere itens na listview. */
int insert_listview_item (
  HWND listview, int item, char *item_text, char *sub1, char *sub2, char *sub3, char *sub4, char *sub5)
{
  LVITEMA listItem;
	memset(&listItem, 0, sizeof(LVITEM));
  
  listItem.mask = LVIF_IMAGE | LVIF_TEXT;
  listItem.cchTextMax = 256;
  listItem.iItem = item;
  listItem.iSubItem = 0;
  listItem.iImage = 0;
  listItem.pszText = item_text;
  SendMessage(listview, LVM_SETITEMSTATE, 0, (LPARAM)&listItem);
  SendMessage(listview,LVM_INSERTITEM,0,(LPARAM)&listItem);
  
  listItem.iSubItem = 1;
  listItem.pszText = sub1;
  SendMessage(listview,LVM_SETITEM,0,(LPARAM)&listItem);
  
  listItem.iSubItem = 2;
  listItem.pszText = sub2;
  SendMessage(listview,LVM_SETITEM,0,(LPARAM)&listItem);
  
  listItem.iSubItem = 3;
  listItem.pszText = sub3;
  SendMessage(listview,LVM_SETITEM,0,(LPARAM)&listItem);
  
  listItem.iSubItem = 4;
  listItem.pszText = sub4;
  SendMessage(listview,LVM_SETITEM,0,(LPARAM)&listItem);
  
  listItem.iSubItem = 5;
  listItem.pszText = sub5;
  SendMessage(listview,LVM_SETITEM,0,(LPARAM)&listItem);
  
  ListView_SetItemState(listview, 0, 0, LVIS_SELECTED | LVIS_FOCUSED);
  ListView_EnsureVisible(listview, item, TRUE);
  
  return TRUE;
}

/* Cria listview. */
HWND create_list_view (HWND parent) 
{
  RECT rclv;
  GetClientRect(parent, &rclv); 
  
  HWND lv = CreateWindowA(WC_LISTVIEW, "",
    WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_VISIBLE,
    0, 0, rclv.right - rclv.left, rclv.bottom - rclv.top,
    parent, (HMENU) HM_LIST_VIEW, GetModuleHandle(NULL), NULL); 
  
  return lv;
}

/* Insere colunas na listview. */
int init_list_view (HWND listview) 
{
  LVCOLUMNA lvc;

  char *strings [] = {
    "Number", "Source", "Destination", "Protocol", "Length", "Information",
    NULL
  };
  
  for (int a=0; strings[a]!=NULL; a++)
  {
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.iSubItem = a;
    lvc.pszText = strings[a];
    lvc.fmt = LVCFMT_LEFT;
    
    switch (a)
    {
    case 0: lvc.cx = 70; break;
    case 3: lvc.cx = 70; break;
    case 4: lvc.cx = 70; break;
    case 5: lvc.cx = 840; break;
    default:
      lvc.cx = 100;
    }
    
    if (ListView_InsertColumn(listview, a, &lvc) == -1)
      return FALSE;
  }
  
  return TRUE;
} 

/* Intercepta pacotes. */
void DS_control (void *lparam)
{
  HANDLE handle = (HANDLE) lparam;
  WINDIVERT_ADDRESS addr;
  PWINDIVERT_IPHDR ip_header;
  PWINDIVERT_IPV6HDR ipv6_header;
  PWINDIVERT_ICMPHDR icmp_header;
  PWINDIVERT_ICMPV6HDR icmpv6_header;
  PWINDIVERT_TCPHDR tcp_header;
  PWINDIVERT_UDPHDR udp_header;
  UINT packet_len = 0;
	UINT payload_len = 0;
  PVOID payload = NULL;
  FILE *fp = NULL;
  unsigned char packet [1024];
  char *ptrs [256], path [256];
  
  Sleep(500);
  while (TRUE)
  {
    if (!WinDivertRecv(handle, packet, sizeof(packet), &addr, &packet_len))
      continue;
    
    WinDivertHelperCalcChecksums(packet, packet_len, WINDIVERT_HELPER_NO_REPLACE);
    
		WinDivertHelperParsePacket(packet, packet_len, &ip_header,
      &ipv6_header, &icmp_header, &icmpv6_header, &tcp_header,
      &udp_header, &payload, &payload_len);
    
    if (ip_header != NULL || ipv6_header != NULL || icmp_header != NULL || 
      icmpv6_header != NULL || tcp_header != NULL || udp_header != NULL)
    {
      if (stop_windivert_process == 1)
         continue;
      
      WaitForSingleObject(g_mutex, INFINITE);
      
      /* IPv4 packet. */
      if (ip_header != NULL)
      {
        for (int a=0; a<6; a++)
          if ((ptrs[a] = realloc(ptrs[a], 256)) != NULL)
            memset(ptrs[a], '\0', 256);
        
        UINT8 *src_addr = (UINT8 *)&ip_header->SrcAddr;
        UINT8 *dst_addr = (UINT8 *)&ip_header->DstAddr;
        sprintf(ptrs[0], "%d", (current_packet_index + 1));
        sprintf(ptrs[1], "%u.%u.%u.%u", src_addr[0], src_addr[1], src_addr[2], src_addr[3]);
        sprintf(ptrs[2], "%u.%u.%u.%u", dst_addr[0], dst_addr[1], dst_addr[2], dst_addr[3]);
        sprintf(ptrs[4], "%d", packet_len);
        
        if (tcp_header != NULL) 
        {
          sprintf(ptrs[5], "V:%u - TTL:%u - P:%u - [ TCP ] SrcPort:%u - DstPort:%u - SeqNum:%u - AckNum:%u - Urg:%u "
            "- Ack:%u - Psh:%u - Rst:%u - Syn:%u - Fin:%u - Window:%u - UrgPtr:%u", 
              ip_header->Version, ip_header->TTL, ip_header->Protocol, ntohs(tcp_header->SrcPort), ntohs(tcp_header->DstPort), 
              ntohl(tcp_header->SeqNum), ntohl(tcp_header->AckNum), tcp_header->Urg, tcp_header->Ack, tcp_header->Psh, 
              tcp_header->Rst, tcp_header->Syn, tcp_header->Fin, ntohs(tcp_header->Window), ntohs(tcp_header->UrgPtr));
          memcpy(ptrs[3], "TCP", strlen("TCP"));
        } 
        else if (udp_header != NULL) 
        {
          sprintf(ptrs[5], "V:%u - TTL:%u - P:%u - [ UDP ] SrcPort: %u - DstPort: %u - Length: %u", 
              ip_header->Version, ip_header->TTL, ip_header->Protocol,
              ntohs(udp_header->SrcPort), ntohs(udp_header->DstPort), 
              ntohs(udp_header->Length), ntohs(udp_header->Checksum));
          memcpy(ptrs[3], "UDP", strlen("UDP"));
        } 
        else 
        {
          sprintf(ptrs[5], "V:%u - HL:%u - TOS:%u - L:%u - ID:0x%.4X - RS:%u - DF:%u - MF:%u - FO:%u - TTL:%u - P:%u", 
            ip_header->Version, ip_header->HdrLength, ntohs(ip_header->TOS), ntohs(ip_header->Length), ntohs(ip_header->Id),
            WINDIVERT_IPHDR_GET_RESERVED(ip_header), WINDIVERT_IPHDR_GET_DF(ip_header), WINDIVERT_IPHDR_GET_MF(ip_header),
            ntohs(WINDIVERT_IPHDR_GET_FRAGOFF(ip_header)), ip_header->TTL, ip_header->Protocol);
          
          if (icmp_header != NULL)
            memcpy(ptrs[3], "ICMP", strlen("ICMP"));
          if (icmpv6_header != NULL)
            memcpy(ptrs[3], "ICMPv6", strlen("ICMPv6"));
          else
            memcpy(ptrs[3], "IPv4", strlen("IPv4"));
        }
        
        insert_listview_item(
          listview, current_packet_index, ptrs[0], ptrs[1], ptrs[2], ptrs[3], ptrs[4], ptrs[5]);
        current_packet_index++;
      }
      
      /* IPv6 packet. */
      else if (ipv6_header != NULL)
      {
        for (int a=0; a<6; a++)
          if ((ptrs[a] = realloc(ptrs[a], 256)) != NULL)
            memset(ptrs[a], '\0', 256);
        
        UINT16 *src_addr = (UINT16 *)&ipv6_header->SrcAddr;
        UINT16 *dst_addr = (UINT16 *)&ipv6_header->DstAddr;
        
        sprintf(ptrs[0], "%d", (current_packet_index + 1));
        sprintf(ptrs[1], "%x:%x:%x:%x", ntohs(src_addr[0]), ntohs(src_addr[1]), ntohs(src_addr[2]), ntohs(src_addr[3]));
        sprintf(ptrs[2], "%x:%x:%x:%x", ntohs(dst_addr[0]), ntohs(dst_addr[1]), ntohs(dst_addr[2]), ntohs(dst_addr[3]));
        sprintf(ptrs[4], "%d", packet_len);
        
        if (tcp_header != NULL)
        {
          sprintf(ptrs[5], 
            "V:%u - TC:%u - FL:%u - LG:%u - NH:%u - HL:%u [ TCP ] SrcPort:%u - DstPort:%u - "
            "SeqNum:%u - AckNum:%u - Urg:%u - Ack:%u - Psh:%u - Rst:%u - Syn:%u - Fin:%u - Window:%u - UrgPtr:%u",
            ipv6_header->Version, WINDIVERT_IPV6HDR_GET_TRAFFICCLASS(ipv6_header), 
            ntohl(WINDIVERT_IPV6HDR_GET_FLOWLABEL(ipv6_header)),
            ntohs(ipv6_header->Length), ipv6_header->NextHdr, ipv6_header->HopLimit, 
            ntohs(tcp_header->SrcPort), ntohs(tcp_header->DstPort), 
            ntohl(tcp_header->SeqNum), ntohl(tcp_header->AckNum), tcp_header->Urg, tcp_header->Ack, tcp_header->Psh, 
            tcp_header->Rst, tcp_header->Syn, tcp_header->Fin, ntohs(tcp_header->Window), ntohs(tcp_header->UrgPtr));
          memcpy(ptrs[3], "IPv6 + TCP", strlen("IPv6 + TCP"));
        } 
        else if (udp_header != NULL) 
        {
          sprintf(ptrs[5], 
            "V:%u - TC:%u - FL:%u - LG:%u - NH:%u - HL:%u [ UDP ] - DstPort: %u - Length: %u",
            ipv6_header->Version, WINDIVERT_IPV6HDR_GET_TRAFFICCLASS(ipv6_header), 
            ntohl(WINDIVERT_IPV6HDR_GET_FLOWLABEL(ipv6_header)),
            ntohs(ipv6_header->Length), ipv6_header->NextHdr, ipv6_header->HopLimit,
            ntohs(udp_header->SrcPort), ntohs(udp_header->DstPort), 
            ntohs(udp_header->Length), ntohs(udp_header->Checksum));
          memcpy(ptrs[3], "IPv6 + UDP", strlen("IPv6 + UDP"));
        } 
        else 
        {
          sprintf(ptrs[5], "V:%u - TC:%u - FL:%u - LG:%u - NH:%u - HL:%u",
            ipv6_header->Version, WINDIVERT_IPV6HDR_GET_TRAFFICCLASS(ipv6_header), 
            ntohl(WINDIVERT_IPV6HDR_GET_FLOWLABEL(ipv6_header)),
            ntohs(ipv6_header->Length), ipv6_header->NextHdr, ipv6_header->HopLimit);
          
          if (icmp_header != NULL)
            memcpy(ptrs[3], "ICMP", strlen("ICMP"));
          if (icmpv6_header != NULL)
            memcpy(ptrs[3], "ICMPv6", strlen("ICMPv6"));
          else
            memcpy(ptrs[3], "IPv6", strlen("IPv6"));
        }
        
        insert_listview_item(
          listview, current_packet_index, ptrs[0], ptrs[1], ptrs[2], ptrs[3], ptrs[4], ptrs[5]);
        current_packet_index++;
      }
      
      /* Pacote desconhecido. */
      else {
       insert_listview_item(listview, current_packet_index, "Unknown packet", "", "", "", "", "");
       current_packet_index++;
      }
      
      /* > Salva dados do pacote em arquivo de log. */
      memset(path, '\0', 256);
      sprintf(path, "log\\%d.log", (current_packet_index - 1));
      
      if ((fp = fopen(path, "w")) != NULL)
      {        
        fprintf(fp, "Item: %d\r\nDirection: %u\r\nInterface index: %u\r\n"
          "Sub-interface index: %u\r\n\r\n",
            current_packet_index, addr.Direction, addr.IfIdx, addr.SubIfIdx);
        
        /* IPv4 packet. */
        if (ip_header != NULL)
        {
          UINT8 *src_addr = (UINT8 *)&ip_header->SrcAddr;
          UINT8 *dst_addr = (UINT8 *)&ip_header->DstAddr;
        
          fprintf(fp, 
            "Protocol: IP (Internet Protocol)\r\n"
            "Version: %u\r\nHeader length: %u\r\nTOS (type of service): %u\r\n"
            "Total length: %u\r\nIdentification: 0x%.4X\r\n", 
              ip_header->Version, ip_header->HdrLength, ntohs(ip_header->TOS), 
              ntohs(ip_header->Length), ntohs(ip_header->Id));
          
          fprintf(fp, 
            "Reserved: %u\r\n"
            "DF: %u\r\nMF: %u\r\nFragOff: %u\r\nTTL: %u\r\nProtocol: %u\r\nChecksum: 0x%.4X\r\n"
            "Source address: %u.%u.%u.%u\r\nDestination address: %u.%u.%u.%u\r\n\r\n", 
              WINDIVERT_IPHDR_GET_RESERVED(ip_header), WINDIVERT_IPHDR_GET_DF(ip_header),
              WINDIVERT_IPHDR_GET_MF(ip_header), ntohs(WINDIVERT_IPHDR_GET_FRAGOFF(ip_header)), 
              ip_header->TTL, ip_header->Protocol, ntohs(ip_header->Checksum),
              src_addr[0], src_addr[1], src_addr[2], src_addr[3],
              dst_addr[0], dst_addr[1], dst_addr[2], dst_addr[3]);
        }
        
        /* IPv6 packet. */
        if (ipv6_header != NULL)
        {
          UINT16 *src_addr = (UINT16 *)&ipv6_header->SrcAddr;
          UINT16 *dst_addr = (UINT16 *)&ipv6_header->DstAddr;
          
          fprintf(fp, 
            "Protocol: IP (Internet Protocol)\r\n"
            "Version: %u\r\nTrafficClass: %u\r\nFlowLabel: %u\r\nLength: %u\r\n"
            "NextHdr: %u\r\nHopLimit: %u\r\nSource address: ",
              ipv6_header->Version, WINDIVERT_IPV6HDR_GET_TRAFFICCLASS(ipv6_header),
              ntohl(WINDIVERT_IPV6HDR_GET_FLOWLABEL(ipv6_header)),
              ntohs(ipv6_header->Length), ipv6_header->NextHdr, ipv6_header->HopLimit);
          
          for (int i = 0; i < 8; i++)
            fprintf(fp, "%x%c", ntohs(src_addr[i]), (i == 7? ' ': ':'));
          fprintf(fp, "\r\nDestination address: ");
          for (int i = 0; i < 8; i++) {
            fprintf(fp, "%x", ntohs(dst_addr[i]));
            if (i != 7)
              fprintf(fp, ":");
          }
          
          fprintf(fp, "\r\n\r\n");
        }
        
        /* ICMP packet. */
        if (icmp_header != NULL)
        {
          fprintf(fp, "Protocol: ICMP (Internet Control Message Protocol)\r\n"
            "Type: %u\r\nCode: %u\r\nChecksum: 0x%.4X\r\nBody: 0x%.8X\r\n\r\n",
              icmp_header->Type, icmp_header->Code, ntohs(icmp_header->Checksum),
              ntohl(icmp_header->Body));
        }
        
        /* ICMP v6 packet. */
        if (icmpv6_header != NULL)
        {
          fprintf(fp, "Protocol: ICMP V6 (Internet Control Message Protocol)\r\n"
            "Type: %u\r\nCode: %u\r\nChecksum: 0x%.4X\r\nBody: 0x%.8X\r\n\r\n",
              icmpv6_header->Type, icmpv6_header->Code, ntohs(icmpv6_header->Checksum), 
              ntohl(icmpv6_header->Body));
        }
        
        /* TCP packet. */
        if (tcp_header != NULL)
        {
          fprintf(fp, 
            "Protocol: TCP (Transmission Control Protocol)\r\n"
            "Source port: %u\r\nDestination port: %u\r\nSequence number: %u\r\n"
            "Acknowledgment number: %u\r\nHeader length: %u\r\nReserved1: %u\r\nReserved2: %u\r\n", 
              ntohs(tcp_header->SrcPort), ntohs(tcp_header->DstPort),
              ntohl(tcp_header->SeqNum), ntohl(tcp_header->AckNum),
              tcp_header->HdrLength, tcp_header->Reserved1,
              tcp_header->Reserved2);
          
          fprintf(fp, 
            "URG: %u\r\nACK: %u\r\nPSH: %u\r\nRST: %u\r\nSYN: %u\r\nFIN: %u\r\n"
            "Window: %u\r\nChecksum: 0x%.4X\r\nUrgent Pointer: %u\r\n\r\n",
              tcp_header->Urg, tcp_header->Ack,
              tcp_header->Psh, tcp_header->Rst, tcp_header->Syn,
              tcp_header->Fin, ntohs(tcp_header->Window),
              ntohs(tcp_header->Checksum), ntohs(tcp_header->UrgPtr));
        }
        
        /* UDP packet. */
        if (udp_header != NULL)
        {
          fprintf(fp, "Protocol: UDP\r\nSource port: %u\r\nDestination port"
            ": %u\r\nLength: %u\r\nChecksum: 0x%.4X\r\n\r\n",
            ntohs(udp_header->SrcPort), ntohs(udp_header->DstPort),
            ntohs(udp_header->Length), ntohs(udp_header->Checksum));
        }
        
        /* Packet payload. */
        for (int i = 0; i < packet_len; i++)
          fprintf(fp, "%.2X", (UINT8)packet[i]);
        fprintf(fp, "\r\n\r\n");
        for (int i = 0; i < packet_len; i++) {
          if (isprint(packet[i]))
            fprintf(fp, "%c", packet[i]);
          else
            fprintf(fp, ".");
        }
        
        fprintf(fp, "\r\n\r\n");
        fclose(fp);
      }
      
      ReleaseMutex(g_mutex);
    }
  }
}

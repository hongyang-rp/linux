
#ifndef _wl_escan_
#define _wl_escan_
#include <linuxver.h>
#if defined(WL_WIRELESS_EXT)
#include <wl_iw.h>
#endif /* WL_WIRELESS_EXT */
#include <wl_android_ext.h>
#include <wl_iapsta.h>
#include <dhd_config.h>

#define ESCAN_BUF_SIZE (64 * 1024)

#define WL_ESCAN_TIMER_INTERVAL_MS	10000 /* Scan timeout */

/* donlge escan state */
enum escan_state {
	ESCAN_STATE_DOWN,
	ESCAN_STATE_IDLE,
	ESCAN_STATE_SCANING
};

typedef struct wl_escan_info {
	struct net_device *dev;
	bool scan_params_v2;
	dhd_pub_t *pub;
	timer_list_compat_t scan_timeout; /* Timer for catch scan event timeout */
	int escan_state;
	int ioctl_ver;
	u8 escan_buf[ESCAN_BUF_SIZE];
	wl_scan_results_v109_t *bss_list;
	u8 *escan_ioctl_buf;
	struct mutex usr_sync; /* maily for up/down synchronization */
	int autochannel;
	int best_2g_ch;
	int best_5g_ch;
	int best_6g_ch;
#if defined(RSSIAVG)
	wl_rssi_cache_ctrl_t g_rssi_cache_ctrl;
	wl_rssi_cache_ctrl_t g_connected_rssi_cache_ctrl;
#endif
#if defined(BSSCACHE)
	wl_bss_cache_ctrl_t g_bss_cache_ctrl;
#endif
} wl_escan_info_t;

#if defined(WLMESH)
enum mesh_info_id {
	MESH_INFO_MASTER_BSSID = 1,
	MESH_INFO_MASTER_CHANNEL,
	MESH_INFO_HOP_CNT,
	MESH_INFO_PEER_BSSID
};

#define MAX_HOP_LIST 10
typedef struct wl_mesh_params {
	struct ether_addr master_bssid;
	uint16 master_channel;
	uint hop_cnt;
	struct ether_addr peer_bssid[MAX_HOP_LIST];
	uint32 scan_channel;
} wl_mesh_params_t;
bool wl_escan_mesh_info(struct net_device *dev,
	struct wl_escan_info *escan, struct ether_addr *peer_bssid,
	struct wl_mesh_params *mesh_info);
bool wl_escan_mesh_peer(struct net_device *dev,
	struct wl_escan_info *escan, wlc_ssid_t *cur_ssid, uint16 cur_chan, bool sae,
	struct wl_mesh_params *mesh_info);
#endif /* WLMESH */
int wl_escan_drv_acs_scan(struct net_device *dev, uint32 band,
	wl_scan_info_t *scan_info);
int wl_escan_drv_apcs(struct net_device *dev, uint32 band, wl_scan_info_t *scan_info);
int wl_escan_set_scan(struct net_device *dev, wl_scan_info_t *scan_info);
void wl_escan_passive_chan_scan(struct net_device *dev);
#if defined(WL_WIRELESS_EXT)
int wl_escan_get_scan(struct net_device *dev,
	struct iw_request_info *info, struct iw_point *dwrq, char *extra);
#endif
int wl_ext_drv_scan(struct net_device *dev, uint32 band, wl_scan_info_t *scan_info);
int wl_escan_attach(struct net_device *dev);
void wl_escan_detach(struct net_device *dev);
int wl_escan_event_attach(struct net_device *dev, int ifidx);
int wl_escan_event_dettach(struct net_device *dev, int ifidx);
int wl_escan_up(struct net_device *dev);
void wl_escan_down(struct net_device *dev);

#endif /* _wl_escan_ */

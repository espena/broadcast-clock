#ifndef UBX_TYPES_HPP
#define UBX_TYPES_HPP

#include <cstdint>

namespace ubx {
  

  typedef struct message_struct {
    uint8_t cls;
    uint8_t id;
  } message_t;

  [[maybe_unused]] const static char *time_mode[ ] = {
    "Disabled",
    "Survey-in",
    "Fixed mode",
    "Unknown"
  };

  [[maybe_unused]] const static char *gnss_id[ ] = {
    "GPS",
    "SBAS",
    "Galileo",
    "BeiDou",
    "IMES",
    "QZSS",
    "GLONASS",
    "Reserved"
  };

  [[maybe_unused]] const static char *utc_standard_timesource[ ] = {
    "Information not available",
    "Communications Research Labratory (CRL), Tokyo, Japan",
    "National Institute of Standards and Technology (NIST)",
    "U.S. Naval Observatory (USNO)",
    "International Bureau of Weights and Measures (BIPM)",
    "European laboratories",
    "Former Soviet Union (SU)",
    "National Time Service Center (NTSC), China",
    "National Physics Laboratory India (NPLI)",
    "Unknown"
  };
  
  namespace message {

    namespace ack {
      static const uint8_t cls = 0x05;
      static const uint8_t ack = 0x01;
      static const uint8_t nak = 0x00;

    }

    namespace cfg {
      static const uint8_t cls = 0x06;
      static const uint8_t ant = 0x13;
      static const uint8_t cfg = 0x09;
      static const uint8_t prt = 0x00;
      static const uint8_t msg = 0x01;
      static const uint8_t tp5 = 0x31;
      static const uint8_t tmode2 = 0x3d;
      static const uint8_t tmode3 = 0x71;
      static const uint8_t gnss = 0x3e;
      static const uint8_t rate = 0x08;
      static const uint8_t rst = 0x04;

    }

    namespace log {
      static const uint8_t cls = 0x21;
      static const uint8_t retrievebatch = 0x10;
    }

    namespace nav {
      static const uint8_t cls = 0x01;
      static const uint8_t status = 0x03;
      static const uint8_t timegps = 0x20;
      static const uint8_t timeutc = 0x21;
      static const uint8_t clock = 0x22;
      static const uint8_t sat = 0x35;
      static const uint8_t svin = 0x3b;

    }

    namespace mon {
      static const uint8_t cls = 0x0a;
      static const uint8_t ver = 0x04;
      static const uint8_t hw = 0x09;

    }

    namespace tim {
      static const uint8_t cls = 0x0d;
      static const uint8_t tm2 = 0x03;
      static const uint8_t svin = 0x04;

    }

  }

  typedef struct cfg_ant_struct {
    struct {
      uint16_t svcs : 1;
      uint16_t scd : 1;
      uint16_t ocd : 1;
      uint16_t pdwn_on_scd : 1;
      uint16_t recovery : 1;
      uint16_t reserved : 11;
    } flags;
    struct {
      uint16_t pin_switch : 5;
      uint16_t pin_scd : 5;
      uint16_t pin_ocd : 5;
      uint16_t reconfig : 1;
    } pins;
  } cfg_ant_t;

  typedef struct cfg_cfg_struct {
    struct {
      uint32_t io_port : 1;
      uint32_t msg_conf : 1;
      uint32_t inf_msg : 1;
      uint32_t nav_conf : 1;
      uint32_t rxm_conf : 1;
      uint32_t reserved0 : 3;
      uint32_t sen_conf : 1;
      uint32_t rinv_conf : 1;
      uint32_t ant_conf : 1;
      uint32_t log_conf : 1;
      uint32_t fts_conf : 1;
      uint32_t reserved1 : 19;
    } clear_mask;
    struct {
      uint32_t io_port : 1;
      uint32_t msg_conf : 1;
      uint32_t inf_msg : 1;
      uint32_t nav_conf : 1;
      uint32_t rxm_conf : 1;
      uint32_t reserved0 : 3;
      uint32_t sen_conf : 1;
      uint32_t rinv_conf : 1;
      uint32_t ant_conf : 1;
      uint32_t log_conf : 1;
      uint32_t fts_conf : 1;
      uint32_t reserved1 : 19;
    } save_mask;
    struct {
      uint32_t io_port : 1;
      uint32_t msg_conf : 1;
      uint32_t inf_msg : 1;
      uint32_t nav_conf : 1;
      uint32_t rxm_conf : 1;
      uint32_t reserved0 : 3;
      uint32_t sen_conf : 1;
      uint32_t rinv_conf : 1;
      uint32_t ant_conf : 1;
      uint32_t log_conf : 1;
      uint32_t fts_conf : 1;
      uint32_t reserved1 : 19;
    } load_mask;
    struct {
      uint8_t dev_bbr : 1;
      uint8_t dev_flash : 1;
      uint8_t dev_eeprom : 1;
      uint8_t reserved0 : 1;
      uint8_t dev_spi_flash : 1;
      uint8_t reserved1 : 3;
    } device_mask;
  } cfg_cfg_t;

  typedef struct tim_svin_struct {
    uint32_t dur;
    int32_t mean_x;
    int32_t mean_y;
    int32_t mean_z;
    uint32_t mean_v;
    uint32_t obs;
    uint8_t valid;
    uint8_t active;
    uint16_t reserved;
  } tim_svin_t;

  typedef struct nav_sat_satellite_struct {
    uint8_t gnss_id;
    uint8_t sv_id;
    uint8_t cno;
    int8_t elev;
    int16_t azim;
    int16_t pr_res;
    uint32_t flags;
  } nav_sat_satellite_t;

  typedef struct nav_sat_struct {
    uint32_t i_tow;
    uint8_t version;
    int8_t num_svs;
    uint16_t reserved1;
    nav_sat_satellite_t satellites[ 32 ];
  } nav_sat_t;

  typedef struct nav_svin_struct {
    uint8_t version;
    uint8_t reserved0[ 3 ];
    uint32_t i_tow;
    uint32_t dur;
    int32_t mean_x;
    int32_t mean_y;
    int32_t mean_z;
    int8_t mean_x_hp;
    int8_t mean_y_hp;
    int8_t mean_z_hp;
    uint8_t reserved1;
    uint32_t mean_acc;
    uint32_t obs;
    uint8_t valid;
    uint8_t active;
    uint16_t reserved2;
  } nav_svin_t;

  typedef struct nav_clock_struct {
    uint32_t i_tow;
    int32_t clk_bias;
    int32_t clk_drift;
    uint32_t t_acc;
    uint32_t f_acc;
  } nav_clock_t;

  typedef struct nav_timegps_struct {
    uint32_t i_tow;
    int32_t f_tow;
    int16_t week;
    int8_t leap_s;
    struct {
      uint8_t valid_tow : 1;
      uint8_t valid_week : 1;
      uint8_t leap_s : 1;
      uint8_t reserved : 5;
    } flags;
    uint32_t t_acc;
  } nav_timegps_t;

  typedef struct nav_timeutc_struct {
    uint32_t i_tow;
    uint32_t t_acc;
    int32_t nano;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t valid;
  } nav_timeutc_t;

  typedef struct tim_tm2_struct {
    uint8_t channel;
    struct {
      uint8_t time_mode : 1;
      uint8_t run : 1;
      uint8_t new_falling_edge : 1;
      uint8_t time_base : 2;
      uint8_t utc : 1;
      uint8_t time : 1;
      uint8_t new_rising_edge : 1;
    } flags;
    uint16_t count;
    uint16_t wn_r;
    uint16_t wn_f;
    uint32_t tow_ms_r;
    uint32_t tow_sub_ms_r;
    uint32_t tow_ms_f;
    uint32_t tow_sub_ms_f;
    uint32_t acc_est;
  } tim_tm2_t;

  typedef struct mon_hw_struct {
    uint32_t pin_sel;
    uint32_t pin_bank;
    uint32_t pin_dir;
    uint32_t pin_val;
    uint16_t noise_per_ms;
    uint16_t agc_cnt;
    uint8_t a_status;
    uint8_t a_power;
    uint8_t flags;
    uint8_t reserved1;
    uint32_t used_mask;
    uint8_t vp[ 17 ];
    uint8_t cw_suppression;
    uint16_t reserved2;
    uint32_t pin_irq;
    uint32_t pull_h;
    uint32_t pull_l;
  } mon_hw_t;

  typedef struct mon_ver_struct {
    char sw_version[ 30 ];
    char hw_version[ 10 ];
  } mon_ver_t;

  typedef struct cfg_rst_struct {
    uint16_t nav_bbr_mask;
    uint8_t reset_mode;
    uint8_t reserved;
  } cfg_rst_t;

  typedef struct cfg_rate_struct {
    uint16_t meas_rate;
    uint16_t nav_rate;
    uint16_t time_ref;
  } cfg_rate_t;

  typedef struct cfg_tmode3_struct {
    uint8_t version;
    uint8_t reserved0;
    uint16_t flags;
    int32_t ecef_x_or_lat;
    int32_t ecef_y_or_lon;
    int32_t ecef_z_or_alt;
    int8_t ecef_x_or_lat_hp;
    int8_t ecef_y_or_lon_hp;
    int8_t ecef_z_or_alt_hp;
    uint8_t reserved1;
    uint32_t fixed_pos_acc;
    uint32_t svin_min_dur;
    uint32_t svin_acc_limit;
    uint64_t reserved2;
  } cfg_tmode3_t;
  
  typedef struct cfg_tmode2_struct {
    uint8_t time_mode;
    uint8_t reserved1;
    uint16_t flags;
    int32_t ecef_x_or_lat;
    int32_t ecef_y_or_lon;
    int32_t ecef_z_or_alt;
    uint32_t fixed_pos_acc;
    uint32_t svin_min_dur;
    uint32_t svin_acc_limit;
  } cfg_tmode2_t;

  typedef struct cfg_tp5_struct {
    uint8_t tp_idx;
    uint8_t version;
    uint16_t reserved1;
    int16_t antenna_cable_delay;
    int16_t rf_group_delay;
    uint32_t freq_period;
    uint32_t freq_period_lock;
    uint32_t pulse_len_ratio;
    uint32_t pulse_len_ratio_lock;
    int32_t user_config_delay;
    struct {
      uint32_t active : 1;
      uint32_t lock_gps_freq : 1;
      uint32_t locked_other_set : 1;
      uint32_t is_freq : 1;
      uint32_t is_lenght : 1;
      uint32_t aligh_to_tow : 1;
      uint32_t polarity : 1;
      uint32_t grid_utc_gps : 1;
      uint32_t reserved : 24;
    } flags;
  } cfg_tp5_t;

  typedef struct cfg_gnss_block_struct {
    uint8_t gnss_id;
    uint8_t res_trk_ch;
    uint8_t max_trk_ch;
    uint8_t reserved;
    struct {
      uint32_t enable : 1;
      uint32_t reserved1 : 15;
      uint32_t sig_cfg_mask : 8;
      uint32_t reserved2 : 8;
    } flags;
  } cfg_gnss_block_t;
  
  typedef struct cfg_gnss_struct {
    uint8_t msg_ver;
    uint8_t num_trk_ch_hw;
    uint8_t num_trk_ch_use;
    uint8_t num_config_blocks;
    cfg_gnss_block_t blocks[ 32 ];
  } cfg_gnss_t;

  typedef struct cfg_prt_ddc_struct {
    uint8_t port_id;
    uint8_t reserved0;
    uint16_t tx_ready;
    uint32_t mode;
    uint32_t reserved2;
    uint16_t in_proto_mask;
    uint16_t out_proto_mask;
    uint16_t flags;
    uint16_t reserved3;
  } cfg_prt_ddc_t;

} // namespace ubx

#endif // UBX_STUCTS_HPP
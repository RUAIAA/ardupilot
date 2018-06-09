#pragma once
#include <inttypes.h>
#include <AP_Param/AP_Param.h>
/*
 *
 * implements the
 *
 */


class AP_AuvsiDeathSpiral
{

	protected:
		//RTL
		AP_Int8 _double_rtl_enable;
		AP_Float _double_rtl_timeout;
		//needs three enables to trigger AUTO DEATH
		AP_Int8 _auto_death_enable;
		AP_Int8 _auto_death_enable2;
		AP_Int8 _auto_death_enable3;
		//timeout for auto death
		AP_Float _auto_death_timeout;

		//enables manual GCS death
		AP_Int8 _man_death_enable;
		//triggers GCS death
		AP_Int8 _man_death_trigger;

	private:
		int _auto_spiral_state;
		int _double_rtl_state;
	public:
		static const struct AP_Param::GroupInfo var_info[];

		enum auto_toggle{
			AUTO_SPIRAL_ON  =43,
		};
		enum man_toggle{
			MAN_SPIRAL_ON=42,
		};
		enum spiral_state{
			STATE_NO_FAILSAFE =0,
			STATE_TRIGGERED=1,
		};
		enum rtl_state{
			STATE_NO_RTL=0,
			STATE_RTL=1,
		};
		enum rtl_toggle{
			AUVSI_RTL_DISABLED =0,
			AUVSI_RTL_ENABLED=1
		};





	AP_AuvsiDeathSpiral(void)
	{
		_auto_spiral_state = STATE_NO_FAILSAFE;
		AP_Param::setup_object_defaults(this,var_info);
	};


	//checks for death spiral conditions using heartbeats
	//and last vaid ch3 signal after short fs has been triggered
	void auto_check(uint32_t last_heartbeat_ms, uint32_t last_valid_rc_ms);
	bool should_death_spiral(void);
	bool is_auto_enabled(void);
	bool is_man_enabled(void);

	bool rtl_check(uint32_t last_heartbeat_ms,uint32_t last_valid_rc_ms);




};

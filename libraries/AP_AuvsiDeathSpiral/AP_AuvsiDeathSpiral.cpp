#include <AP_HAL/AP_HAL.h>
#include "AP_AuvsiDeathSpiral.h"
const AP_Param::GroupInfo AP_AuvsiDeathSpiral::var_info[]={
	//@Param: AUTO_ENABLE
	//@DisplayName: Enable Death spiral switch 1 (default 0)
	//Description: This is one step in enabling auto death spiral (43 to enable)
	//@User: Advanced
	AP_GROUPINFO("AUTO_EN", 0, AP_AuvsiDeathSpiral,_auto_death_enable,0),//,AP_PARAM_FLAG_ENABLE),
	//@Param: AUTO_ENABLE2
	//@DisplayName: Enable Death spiral switch 2 (default 0)
	//@Description: This is the second step in enabling auto death spiral (43 to enable)
	//@User: Adavanced
	AP_GROUPINFO("AUTO_EN2", 1, AP_AuvsiDeathSpiral,_auto_death_enable2,0),//,AP_PARAM_FLAG_ENABLE),
	//@Param: AUTO_ENABLE3
	//@DisplayName: Enable Death spiral switch 3 (default 0)
	//@Description: This is the last step in enabling auto death spiral (43 to enable)
	//@User: Advanced
	AP_GROUPINFO("AUTO_EN3",2, AP_AuvsiDeathSpiral,_auto_death_enable3,0),//,AP_PARAM_FLAG_ENABLE),
	//@Param: DEATH_SPIRAL_TIMEOUT
	//@DisplayName: Death Spiral Timeout (default 3)
	//@Description: This is the time in MINUTES in when failsafe termination will activate. Triggers after X minutes of loss of RC and GCS to comply with the AUVSI SUAS competition rules
	//@User: Advanced
	//@Units: minutes
	AP_GROUPINFO("TIMEOUT",3,AP_AuvsiDeathSpiral,_auto_death_timeout,3),

	//@Param: MAN_ENABLE
	//@DisplayName: Enable/Disable Manual Death Spiral (default 0)
	//@Description: Set to 42 to enable manual death spiral trigger, set to anyother number to disable
	//@User: Advanced
	AP_GROUPINFO("MAN_EN",4,AP_AuvsiDeathSpiral,_man_death_enable,0),


	//@Param: TRIGGER_DEATH
	//@DisplayName: TRIGGERS DEATH SPIRAL! (default 0)
	//@Description: If 1 is set on MAN_ENABLE this WILL TRIGGER DEATH!
	//@User: Advanced
	AP_GROUPINFO("MAN_TRIG",5,AP_AuvsiDeathSpiral,_man_death_trigger,0),

        //@Param DOUBLE_RTL
	///DisplayName: Set RTL on loss of both comms (default 0)
	//@Description: If set to 1 it will RTL in X seconds
	//@User: Advanced
	AP_GROUPINFO("RTL",6,AP_AuvsiDeathSpiral,_double_rtl_enable,0),

	//@Param: RTL_TIMEOUT
	//@DisplayName:	Set RTL timeout for loss of both comms (default 30)
	//@Description: Will go to RTL in X seconds if loss both comms
	//@User: Adavanced
	//@Units: Seconds
	AP_GROUPINFO("RTL_TIME",7,AP_AuvsiDeathSpiral,_double_rtl_timeout,30),

	AP_GROUPEND


};



bool
AP_AuvsiDeathSpiral::rtl_check(uint32_t last_heartbeat_ms,uint32_t last_valid_rc_ms){
	uint32_t now = AP_HAL::millis();
	if(_double_rtl_enable==AUVSI_RTL_ENABLED &&
			(now-last_heartbeat_ms) >_double_rtl_timeout*1000&&
			(now-last_valid_rc_ms) > _double_rtl_timeout*1000&&
			_double_rtl_state!=STATE_RTL){

			_double_rtl_state=STATE_RTL;
			return true;

	} else if(_double_rtl_enable==AUVSI_RTL_ENABLED&&
		       ((now-last_heartbeat_ms) <_double_rtl_timeout*1000||
		       (now-last_valid_rc_ms)  <_double_rtl_timeout*1000)&&
		       _double_rtl_state==STATE_RTL){

			_double_rtl_state=STATE_NO_RTL;
	}
	return false;
}

/*
 * called in ArduPilot.cpp to check for death spiral status
 * checks based on the last heartbeat and last rc received
 */
void
AP_AuvsiDeathSpiral::auto_check(uint32_t last_heartbeat_ms,uint32_t last_valid_rc_ms){
	uint32_t now = AP_HAL::millis();

	if(is_auto_enabled() &&
	                (now-last_heartbeat_ms) > _auto_death_timeout*60*1000&&
			(now-last_valid_rc_ms)   > _auto_death_timeout*60*1000){
		_auto_spiral_state = STATE_TRIGGERED;

		return;
	}
		_auto_spiral_state = STATE_NO_FAILSAFE;
};

/*
 * called in failsafe.cpp to check whether to terminate aircraft
 *
 */
bool
AP_AuvsiDeathSpiral::should_death_spiral(void){


        if(is_man_enabled()&&_man_death_trigger==STATE_TRIGGERED){
		return true;
	}

	if(is_auto_enabled()&&_auto_spiral_state == STATE_TRIGGERED){

		return true;
	}
	return false;
};


/*
 * used to determine if auto spiral is enabled
 */
bool
AP_AuvsiDeathSpiral::is_auto_enabled(void){
	return ( _auto_death_enable==AUTO_SPIRAL_ON &&
		  _auto_death_enable2==AUTO_SPIRAL_ON&&
		  _auto_death_enable3==AUTO_SPIRAL_ON);
}

/*
 * used to determine if man spiral is enabled
 */
bool
AP_AuvsiDeathSpiral::is_man_enabled(void){
	return (_man_death_enable==MAN_SPIRAL_ON);
}

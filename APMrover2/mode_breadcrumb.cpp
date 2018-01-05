#include "mode.h"
#include "Rover.h"

#if 1
#define Debug(fmt, args ...)  do{hal.console->printf(fmt,args);}while(0);
#else
#define Debug(fmt, args ...)
#endif

bool ModeBreadcrumb::_enter()
{
<<<<<<< HEAD
<<<<<<< HEAD
    //don't call enter again if _crumbs exists
    if (_crumbs != nullptr) {
        return false;
    }

=======

=======
    //don't call enter again if _crumbs exists
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    if (_crumbs != nullptr) {
        return false;
    }

<<<<<<< HEAD

    // constrain the path length, in case the user decided to make the path unreasonably long.
    //_crumbs_max = constrain_int16(_crumbs_max, 0, crumbs_max);
    
    // check if user has disabled Breadcrumbs
    if (_crumbs_max == 0) {
        return false;
    }


>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    // create semaphore
    _crumbs_sem = hal.util->new_semaphore();
    if (_crumbs_sem == nullptr) {
        return false;
    }

<<<<<<< HEAD
    _current_crumb = nullptr;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

    // allocate crumbs queue
    _crumbs = (Location*)calloc(crumbs_max, sizeof(Location));

<<<<<<< HEAD
=======
    // allocate arraysconv
    _crumbs = (Location*)calloc(_crumbs_max, sizeof(Location));
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    _crumbs_tail = 0;
    _crumbs_head = 0;

    lonely_mode = nullptr;
<<<<<<< HEAD
<<<<<<< HEAD

    //reuse guided mode
    if (!ModeGuided::_enter()) {
=======

    // allocate arrays
    _crumbs = (Location*)calloc(_crumbs_max, sizeof(Location));


    if(!ModeGuided::_enter()){
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
=======

    //reuse guided mode
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    if (!ModeGuided::_enter()) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
        free(_crumbs);
        return false;
    }

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    return true;
}

void ModeBreadcrumb::_exit()
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    //reset lonely mode in case we go back into breadcrumb mode
    lonely_mode = nullptr;
    if (_crumbs != nullptr) {
        free(_crumbs);
        //stop usage of freed data
        _crumbs = nullptr;
    }
}

void ModeBreadcrumb::run_lonely_mode()
{
    if (lonely_mode == nullptr) {
=======
        if(_crumbs != nullptr){
            free(_crumbs);
            //stop usage of free'd data
            _crumbs = nullptr;
        }
}

void ModeBreadcrumb::run_lonely_mode(){
    if(lonely_mode == nullptr){
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
=======
    //reset lonely mode in case we go back into breadcrumb mode
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    lonely_mode = nullptr;
    if (_crumbs != nullptr) {
        free(_crumbs);
        //stop usage of freed data
        _crumbs = nullptr;
    }
}

void ModeBreadcrumb::run_lonely_mode()
{
    if (lonely_mode == nullptr) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
        rover.mode_hold.enter();
        lonely_mode = &rover.mode_hold;

        gcs().send_text(MAV_SEVERITY_INFO, "Breadcrumb: Lonely; %s", lonely_mode->name4());
    }

    lonely_mode->update();
}

void ModeBreadcrumb::update()
{

<<<<<<< HEAD
<<<<<<< HEAD
    //get_distance_to_destination returns exactly 0.0f when destination is reached
<<<<<<< HEAD
    if(_current_crumb!=nullptr&&ModeGuided::get_distance_to_destination()!= 0.0f){
        return;
    }

=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

    float distance_to_breadcrumb = ModeGuided::get_distance_to_destination();

    //get_distance_to_destination returns exactly 0.0f when destination is reached
    if (_current_crumb != nullptr && distance_to_breadcrumb != 0.0f) {


<<<<<<< HEAD
        Vector3f to_vehicle = location_3d_diff_NED(rover.current_loc, target_loc);
        const float distance_to_vehicle = to_vehicle.length();

        //assign to default value (won't be used)
        float desired_speed = -1.0f;

        //maintain at greater than distance_to_stop from target
        if (fabsf(distance_to_vehicle) > distance_to_stop) {
            //we need to speed up
            to_vehicle *= closure_speed * 100; // m/s to cm/s (which set_desired_speed takes)
            to_vehicle+=target_vel;

            desired_speed = to_vehicle.length();
        } else if (fabsf(distance_to_vehicle) < distance_to_stop) {
            //too close. stop until target is far enough away
            desired_speed = 0.0f;
=======
    if (_current_crumb!=nullptr&&ModeGuided::get_distance_to_destination()!= 0.0f) {
        //maintain constant distance from target
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
        Vector3f to_vehicle = location_3d_diff_NED(rover.current_loc, target_loc);
        const float distance_to_vehicle = to_vehicle.length();

        //assign to default value (won't be used)
        float desired_speed = -1.0f;

        //maintain at greater than distance_to_stop from target
        if (fabsf(distance_to_vehicle) > distance_to_stop) {
            //we need to speed up
            to_vehicle *= closure_speed * 100; // m/s to cm/s (which set_desired_speed takes)
            to_vehicle+=target_vel;

            desired_speed = to_vehicle.length();
        } else if (fabsf(distance_to_vehicle) < distance_to_stop) {
<<<<<<< HEAD
            //to close stop until target is far enough away
            Mode::set_desired_speed(0);
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
=======
            //too close. stop until target is far enough away
            desired_speed = 0.0f;
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
        }

        //don't change speed if we are distance_to_stop away;
        if (desired_speed != -1.0f) {
            Mode::set_desired_speed(desired_speed);
        }

        // re-use guided mode with set waypoint
        ModeGuided::update();

    } else {

<<<<<<< HEAD
<<<<<<< HEAD
        if (!_crumbs_sem->take_nonblocking()) {
            Debug("%s\n","update failed to get semaphore");
        }
=======
    if (!_crumbs_sem->take_nonblocking()) {
        Debug("%s\n","update failed to get semaphore");
    }
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
=======
        if (!_crumbs_sem->take_nonblocking()) {
            Debug("%s\n","update failed to get semaphore");
        }
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

        uint16_t crumbs_queue_size = (_crumbs_tail >= _crumbs_head) ? (_crumbs_tail - _crumbs_head) : crumbs_max - (_crumbs_head-_crumbs_tail);

        if (crumbs_queue_size == 0) {
            _current_crumb = nullptr;
            _crumbs_sem->give();
            return run_lonely_mode();
        }

        lonely_mode = nullptr;

        _current_crumb = &_crumbs[_crumbs_head++];
<<<<<<< HEAD

        //re-use guided modes waypoint functionality
        ModeGuided::set_desired_location(*_current_crumb);

        //loop around the queue if we hit the end
        if (_crumbs_head >= crumbs_max) {
            _crumbs_head = 0;
        }

<<<<<<< HEAD
=======
    uint16_t size = (_crumbs_tail >= _crumbs_head) ? (_crumbs_tail - _crumbs_head) : _crumbs_max - (_crumbs_head-_crumbs_tail);
    //Debug("SIZE %u\n",size);
    if (size == 0) {
        _current_crumb = nullptr;
>>>>>>> 8617436... Uses guided mode to go to breadcrumb
        _crumbs_sem->give();
    }
<<<<<<< HEAD
<<<<<<< HEAD
=======
      lonely_mode = nullptr;
      _current_crumb = &_crumbs[_crumbs_head++];
      ModeGuided::set_desired_location(*_current_crumb);
      Debug("Got Crumb %lu %lu %lu %u \n",(long)_current_crumb->lat,(long)_current_crumb->lng,(long)_current_crumb->alt,size);
      if(_crumbs_head >=_crumbs_max){
          _crumbs_head = 0;
      }
=======
    lonely_mode = nullptr;
    _current_crumb = &_crumbs[_crumbs_head++];
    ModeGuided::set_desired_location(*_current_crumb);
    Debug("Got Crumb %lu %lu %lu %u \n",(long)_current_crumb->lat,(long)_current_crumb->lng,(long)_current_crumb->alt,size);
    if (_crumbs_head >=_crumbs_max) {
        _crumbs_head = 0;
    }
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
    _crumbs_sem->give();
>>>>>>> 8617436... Uses guided mode to go to breadcrumb
=======

        //re-use guided modes waypoint functionality
        ModeGuided::set_desired_location(*_current_crumb);

        //loop around the queue if we hit the end
        if (_crumbs_head >= crumbs_max) {
            _crumbs_head = 0;
        }

        _crumbs_sem->give();
    }
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

}




void ModeBreadcrumb::mavlink_packet_received(const mavlink_message_t &msg)
{

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

    if (rover.control_mode != &rover.mode_breadcrumb) {
        return;
    }
    if (msg.sysid != target_srcid) {
        return;
    }
    if (msg.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) {
=======

    if(!_crumbs_sem->take_nonblocking()){
        Debug("%s\n","update failed to get semaphore");
    }

    uint16_t size = (_crumbs_tail >= _crumbs_head) ? (_crumbs_tail - _crumbs_head) : _crumbs_max - (_crumbs_head-_crumbs_tail);
    //Debug("SIZE %u\n",size);
    if(size == 0){
        _crumbs_sem->give();
        return run_lonely_mode();
    }
    lonely_mode = nullptr;
    Location crumb = _crumbs[_crumbs_head++];
    Debug("Got Crumb %lu %lu %lu %u \n",(long)crumb.lat,(long)crumb.lng,(long)crumb.alt,size);
    if(_crumbs_head >=_crumbs_max){
        _crumbs_head = 0;
    }
    _crumbs_sem->give();

<<<<<<< HEAD
}

void ModeBreadcrumb::mavlink_packet_received(const mavlink_message_t &msg)
{
    if(rover.control_mode != &rover.mode_breadcrumb){
=======
    //Debug("%u %u\n",msg.sysid,msg.msgid);
    if (rover.control_mode != &rover.mode_breadcrumb) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
        return;
    }
    if (msg.sysid != target_srcid) {
        return;
    }
<<<<<<< HEAD
    if(msg.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT){
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
    if (msg.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
        return;
    }

=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    mavlink_global_position_int_t packet;
    mavlink_msg_global_position_int_decode(&msg, &packet);

<<<<<<< HEAD
<<<<<<< HEAD
    if (!_crumbs_sem->take_nonblocking()) {
        Debug("%s\n","mavlink_packet_received: failed to get semaphore");
        return;
    }

    uint16_t crumbs_queue_size = (_crumbs_tail >= _crumbs_head) ? (_crumbs_tail - _crumbs_head) : crumbs_max - (_crumbs_head-_crumbs_tail);

    if (crumbs_queue_size >= crumbs_max) {
<<<<<<< HEAD
=======
    if(!_crumbs_sem->take_nonblocking()){
=======
    if (!_crumbs_sem->take_nonblocking()) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
        Debug("%s\n","mavlink_packet_received: failed to get semaphore");
        return;
    }
    uint16_t size = (_crumbs_tail >= _crumbs_head) ? (_crumbs_tail - _crumbs_head) : _crumbs_max - (_crumbs_head-_crumbs_tail);
<<<<<<< HEAD
    if(size>=_crumbs_max){
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
    if (size>=_crumbs_max) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
        _crumbs_sem->give();
        Debug("%s\n","mavlink_packet_received: crumb list max count reached");
    }

    //loop back around the queue to the beggining
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    if (_crumbs_tail >= crumbs_max) {
=======
    if(_crumbs_tail >= _crumbs_max) {
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
    if (_crumbs_tail >= _crumbs_max) {
>>>>>>> f52328e... APMrover2-breadcrumb:style changes
=======
    if (_crumbs_tail >= crumbs_max) {
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
        _crumbs_tail = 0;
    }

    _crumbs[_crumbs_tail].lat = packet.lat;
    _crumbs[_crumbs_tail].lng = packet.lon;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members
    _crumbs[_crumbs_tail++].alt = 0.0f; //rover doesn't use alt

    target_loc.lat = packet.lat;
    target_loc.lng = packet.lon;
    target_loc.alt = 0.0f;
    target_vel.x = packet.vx/100.0f; // cm/s to m/s
    target_vel.y = packet.vy/100.0f; // cm/s to m/s
<<<<<<< HEAD
=======
    _crumbs[_crumbs_tail++].alt = packet.relative_alt / 10; // mm -> cm

    target_last_update_ms = AP_HAL::millis();

    Debug("%s\n","mavlink_packet_received added crumb\n");
>>>>>>> 6b11c60... Started Breadcrumb mode. Queues and Dequeues crumbs
=======
>>>>>>> aca8b9f... APM2rover-breadcrumb: style formatting and removed unused members

    _crumbs_sem->give();

}

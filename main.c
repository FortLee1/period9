#include <kipr/botball.h>
void turn_left(double angle);
void turn_right(double angle);
void move_forward(double distanceleft, double distanceright);
void move_backwards(double distanceleft, double distanceirght);
void forward_left(double distance);
void forward_right(double distance);
void servo_up(double angle);
void servo_down(double angle);
void claw_open(double angle);
void claw_close(double angle);
void burning_building();

/*Channel 0 - Post It
Channel 1- Firemen
Channel 2 - Fire Truck
servo up->down (500-1650)
claw open->close (2047-1000)
*/
//testing pull request
int main()
{
    //wait_for_light(0);
    //shut_down_in(118);
    set_servo_position(0, 500);
    set_servo_position(1, 1000);
    enable_servos();
    camera_open();
    
    //get to middle of board
   	msleep(1000);
    turn_left(86);
    msleep(500);
    move_forward(26, 27);
    msleep(500);
    turn_left(120);
    //turn_left(10);
    msleep(500);
    move_forward(4, 5);
    msleep(250);
    
    //two methods between left or right burning center
    
    while (analog(1) < 2800) {
       	camera_update();
   		if (get_object_center_x(0, 1) < 80)
   		{
       		//move towards firetruck
       		move_forward(26, 26);
        	msleep(250);
        	turn_left(90);
       		move_forward(13, 13);
        	turn_left(10);
        
       		//grab firetruck
   			claw_open(2047);
   			servo_down(1650);
   			claw_close(1100);
   			servo_up(700);
        
        	//turn around and place firetruck
        	turn_left(198);
        	msleep(250);
    		move_backwards(3, 3);
        	msleep(250);
        	servo_down(1650);
        	claw_open(1300);
        	servo_up(700);
        	turn_right(17);
        	msleep(250);
        
        	//position in front of firemen for swing
        	move_backwards(10, 10);
        	msleep(500);
        	claw_open(2047);
        
        	//swing out firemen
        	int x = 0;
        	for(x = 0; x < 5; x++) {
        		servo_down(1550);
        		claw_close(1400);
        		servo_up(700);
            	claw_open(2047);
       		 }
        
        	//sweep outside firemen
        	servo_down(1650);
        	//move_forward(16, 16);
        
    }
   	else if (get_object_center_x(0, 1) > 82)
   	{
       	//move towards firetruck
       	move_forward(24, 24);
        msleep(250);
        turn_left(90);
       	move_forward(13, 13);
        turn_left(10);
        
       	//grab firetruck
   		claw_open(2047);
   		servo_down(1650);
   		claw_close(1100);
   		servo_up(700);
        
        //turn around and place firetruck
        turn_left(198);
        msleep(250);
    	move_forward(10, 10);
        msleep(250);
        servo_down(1650);
        claw_open(1300);
        servo_up(700);
        turn_right(17);
        msleep(250);
        
        //position in front of firemen for swing
        move_backwards(15, 15);
        msleep(500);
        claw_open(2047);
        
        //swing out firemen
        int x = 0;
        for(x = 0; x < 5; x++) {
        	servo_down(1550);
        	claw_close(1400);
        	servo_up(700);
            claw_open(2047);
        }
        
        //sweep outside firemen
        servo_down(1650);
        move_forward(16, 16);
   	} 
        
    }
    camera_close();
    
    disable_servos();
    return 0;
}
    
void turn_left(double angle)
{
	mrp(0, 1100, -angle/360 * 120 * 43.75);
    mrp(1, 1100, angle/360 * 120 * 43.75);
    bmd(0);
    bmd(1);
}

void turn_right(double angle)
{
    mrp(0, 1100, angle/360 * 120 * 43.75);
    mrp(1, 1100, -angle/360 * 120 * 43.75);
    bmd(0);
    bmd(1);
}

void move_forward(double distanceleft, double distanceright)
{
    mrp(0, 1080, distanceleft * 260);
    mrp(1, 1185, distanceright * 260);
    bmd(0);
    bmd(1);
}

void move_backwards(double distanceleft, double distanceright)
{
    mrp(0, 1080, -distanceleft * 260);
    mrp(1, 1185, -distanceright * 260);
    bmd(0);
    bmd(1);
}

void forward_left(double distance)
{
    mrp(0, 900, distance * 260);
    mrp(1, 1100, distance * 260);
    bmd(1);
}

void forward_right(double distance)
{
	mrp(0, 1100, distance * 260);
    mrp(1, 900, distance * 260);
    bmd(1);
}

void servo_up(double angle)
{
    set_servo_position(0, angle);
    msleep(1000);
}

void servo_down(double angle)
{
    set_servo_position(0, angle);
    msleep(1000);
}

void claw_open(double angle)
{
    set_servo_position(1, angle);
    msleep(1000);
}

void claw_close(double angle)
{
    set_servo_position(1, angle);
    msleep(1000);
}

void burning_building()
{
    //sense where burning building is
    while(analog(1) < 2450) 
    {
    	camera_update();
        if (get_object_center_x(0, 0) < 77)
        {
             forward_left(1);
        }
        else if (get_object_center_x(0, 0) > 83)
        {
            forward_right(1);
        }
    }
}

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <stdio.h>
#include <fstream>

using namespace std;
#define PI 3.14159265

#define taille 4
int main(int argc, char** argv){
	
	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node;
	tf::TransformListener listener;

	ros::Rate rate(30.0);

	vector<double> right_hand_x;	vector<double> right_hand_roll;
	vector<double> right_hand_y;	vector<double> right_hand_pitch;	
	vector<double> right_hand_z;	vector<double> right_hand_yaw;  

	vector<double> left_hand_x;     vector<double> left_hand_roll;
	vector<double> left_hand_y;     vector<double> left_hand_pitch;
	vector<double> left_hand_z;     vector<double> left_hand_yaw;

        vector<double> right_elbow_x;   vector<double> right_elbow_roll;
	vector<double> right_elbow_y;   vector<double> right_elbow_pitch;
	vector<double> right_elbow_z;   vector<double> right_elbow_yaw;

        vector<double> left_elbow_x;   vector<double> left_elbow_roll;
	vector<double> left_elbow_y;   vector<double> left_elbow_pitch;
	vector<double> left_elbow_z;   vector<double> left_elbow_yaw;

        vector<double> right_shoulder_x;   vector<double> right_shoulder_roll;
	vector<double> right_shoulder_y;   vector<double> right_shoulder_pitch;
	vector<double> right_shoulder_z;   vector<double> right_shoulder_yaw;
  
        vector<double> left_shoulder_x;   vector<double> left_shoulder_roll;
	vector<double> left_shoulder_y;   vector<double> left_shoulder_pitch;
	vector<double> left_shoulder_z;   vector<double> left_shoulder_yaw;
     
	vector<double> head_x;    vector<double> head_roll;
	vector<double> head_y;    vector<double> head_pitch;
	vector<double> head_z;    vector<double> head_yaw;      

        vector<double> neck_x;    vector<double> neck_roll;
	vector<double> neck_y;    vector<double> neck_pitch;
	vector<double> neck_z;    vector<double> neck_yaw;

        vector<double> torso_x;    vector<double> torso_roll;
	vector<double> torso_y;    vector<double> torso_pitch;
	vector<double> torso_z;    vector<double> torso_yaw;

    double right1_x = 0;  
    double right1_y = 0;//for the right hand
    double right1_z = 0;

    double right2_x = 0;  
    double right2_y = 0;//for the right elbow
    double right2_z = 0;

    double right3_x = 0;  
    double right3_y = 0;//for the right shoulder
    double right3_z = 0;

    double left1_x = 0;  
    double left1_y = 0;//for the left hand
    double left1_z = 0;

    double left2_x = 0;  
    double left2_y = 0;//for the left elbow
    double left2_z = 0;

    double left3_x = 0;  
    double left3_y = 0;//for the left shoulder
    double left3_z = 0; 

    double middle1_x = 0;  
    double middle1_y = 0;//for the neck
    double middle1_z = 0;
    
    double middle2_x = 0;  
    double middle2_y = 0;//for the head
    double middle2_z = 0;

    double middle3_x = 0;  
    double middle3_y = 0;
    double middle3_z = 0;
   
    double x_tmp ;
    double y_tmp ;
    double z_tmp ;

    double x_diff;
    double y_diff;
    double z_diff;
 int loop =0;
	while (node.ok() && loop < 20){
		loop++;
		tf::StampedTransform tf_right_hand;
		tf::StampedTransform tf_left_hand;
                tf::StampedTransform tf_neck;
                tf::StampedTransform tf_right_elbow;
                tf::StampedTransform tf_left_elbow; 
                tf::StampedTransform tf_left_shoulder; 
                tf::StampedTransform tf_right_shoulder;  
                tf::StampedTransform tf_head;  

		tf::StampedTransform tf_torso;
		try{
			 ros::Duration timeout(1.0 / 30);
                         ros::Time now = ros::Time(0);//now();
// ---------- FOR THE RIGHT HAND ---------------------------------------------------------------
			
			listener.waitForTransform("/torso_1", "/right_hand_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/right_hand_1", ros::Time(0), tf_right_hand);

			x_tmp = tf_right_hand.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_right_hand.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_right_hand.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - right1_x;
			y_diff = y_tmp - right1_y;
			z_diff = z_tmp - right1_z;

			right1_x = x_tmp;  
			right1_y = y_tmp;
			right1_z = z_tmp;

			//putting the values in vector to save

			right_hand_x.push_back(x_diff);
			right_hand_y.push_back(y_diff);
			right_hand_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_right_hand.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_right_hand=tf_right_hand.getRotation();

                        right_hand_roll.push_back(x_diff);
                        right_hand_pitch.push_back(y_diff);
                        right_hand_yaw.push_back(z_diff);

			cout <<"RIGHT HAND VALUE PUSHED INTO VECTOR" <<endl;

// --------------------- FOR THE LEFT HAND ------------------------------------------------------			
			
			listener.waitForTransform("/torso_1", "/left_hand_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/left_hand_1", ros::Time(0), tf_left_hand);

			x_tmp = tf_left_hand.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_left_hand.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_left_hand.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - left1_x;
			y_diff = y_tmp - left1_y;
			z_diff = z_tmp - left1_z;

			left1_x = x_tmp;  
			left1_y = y_tmp;
			left1_z = z_tmp;

			//putting the values in vector to save

			left_hand_x.push_back(x_diff);
			left_hand_y.push_back(y_diff);
			left_hand_z.push_back(z_diff);
			
			//double left_hand_roll,left_hand_pitch, left_hand_yaw;          // compute rotations
                        tf_left_hand.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_left_hand=tf_left_hand.getRotation();

                        left_hand_roll.push_back(x_diff);
                        left_hand_pitch.push_back(y_diff);
                        left_hand_yaw.push_back(z_diff);

			cout <<"LEFT HAND VALUE PUSHED INTO VECTOR" <<endl;
// ---------- FOR THE NECk -----------------------------------------------------------

			listener.waitForTransform("/torso_1", "/neck_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/neck_1", ros::Time(0), tf_neck);

			x_tmp = tf_neck.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_neck.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_neck.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - middle1_x;
			y_diff = y_tmp - middle1_y;
			z_diff = z_tmp - middle1_z;

			middle1_x = x_tmp;  
			middle1_y = y_tmp;
			middle1_z = z_tmp;

			//putting the values in vector to save

			neck_x.push_back(x_diff);
			neck_y.push_back(y_diff);
			neck_z.push_back(z_diff);
			
			//double left_hand_roll,left_hand_pitch, left_hand_yaw;          // compute rotations
                        tf_neck.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_neck=tf_neck.getRotation();

                        neck_roll.push_back(x_diff);
                        neck_pitch.push_back(y_diff);
                        neck_yaw.push_back(z_diff);

			cout <<"NECk VALUE PUSHED INTO VECTOR" <<endl;
// ---------- FOR THE RIGHT ELBOW ---------------------------------------------------------------
			
			listener.waitForTransform("/torso_1", "/right_elbow_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/right_elbow_1", ros::Time(0), tf_right_elbow);

			x_tmp = tf_right_elbow.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_right_elbow.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_right_elbow.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - right2_x;
			y_diff = y_tmp - right2_y;
			z_diff = z_tmp - right2_z;

			right2_x = x_tmp;  
			right2_y = y_tmp;
			right2_z = z_tmp;

			//putting the values in vector to save

			right_elbow_x.push_back(x_diff);
			right_elbow_y.push_back(y_diff);
			right_elbow_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_right_elbow.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_right_elbow=tf_right_elbow.getRotation();

                        right_elbow_roll.push_back(x_diff);
                        right_elbow_pitch.push_back(y_diff);
                        right_elbow_yaw.push_back(z_diff);

			cout <<"RIGHT ELBOW VALUE PUSHED INTO VECTOR" <<endl;
// ---------- FOR THE LEFT ELBOW ---------------------------------------------------------------
			
			listener.waitForTransform("/torso_1", "/left_elbow_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/left_elbow_1", ros::Time(0), tf_left_elbow);

			x_tmp = tf_left_elbow.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_left_elbow.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_left_elbow.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - left2_x;
			y_diff = y_tmp - left2_y;
			z_diff = z_tmp - left2_z;

			left2_x = x_tmp;  
			left2_y = y_tmp;
			left2_z = z_tmp;

			//putting the values in vector to save

			left_elbow_x.push_back(x_diff);
			left_elbow_y.push_back(y_diff);
			left_elbow_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_left_elbow.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_left_elbow=tf_left_elbow.getRotation();

                        left_elbow_roll.push_back(x_diff);
                        left_elbow_pitch.push_back(y_diff);
                        left_elbow_yaw.push_back(z_diff);

			cout <<"LEFT ELBOW VALUE PUSHED INTO VECTOR" <<endl;
// ---------- FOR THE LEFT SHOULDER ---------------------------------------------------------------
			
			listener.waitForTransform("/torso_1", "/left_shoulder_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/left_shoulder_1", ros::Time(0), tf_left_shoulder);

			x_tmp = tf_left_shoulder.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_left_shoulder.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_left_shoulder.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - left3_x;
			y_diff = y_tmp - left3_y;
			z_diff = z_tmp - left3_z;

			left3_x = x_tmp;  
			left3_y = y_tmp;
			left3_z = z_tmp;

			//putting the values in vector to save

			left_shoulder_x.push_back(x_diff);
			left_shoulder_y.push_back(y_diff);
			left_shoulder_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_left_shoulder.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_left_shoulder=tf_left_shoulder.getRotation();

                        left_shoulder_roll.push_back(x_diff);
                        left_shoulder_pitch.push_back(y_diff);
                        left_shoulder_yaw.push_back(z_diff);

			cout <<"LEFT SHOULDER VALUE PUSHED INTO VECTOR" <<endl;

// ---------- FOR THE RIGHT SHOULDER ---------------------------------------------------------------
			
			listener.waitForTransform("/torso_1", "/right_shoulder_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/torso_1", "/right_shoulder_1", ros::Time(0), tf_right_shoulder);

			x_tmp = tf_right_shoulder.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_right_shoulder.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_right_shoulder.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - right3_x;
			y_diff = y_tmp - right3_y;
			z_diff = z_tmp - right3_z;

			right3_x = x_tmp;  
			right3_y = y_tmp;
			right3_z = z_tmp;

			//putting the values in vector to save

			right_shoulder_x.push_back(x_diff);
			right_shoulder_y.push_back(y_diff);
			right_shoulder_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_right_shoulder.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_right_shoulder=tf_right_shoulder.getRotation();

                        right_shoulder_roll.push_back(x_diff);
                        right_shoulder_pitch.push_back(y_diff);
                        right_shoulder_yaw.push_back(z_diff);

			cout <<"RIGHT SHOULDER VALUE PUSHED INTO VECTOR" <<endl;
// --------------------- FOR THE HEAD ------------------------------------------------------			
			
			listener.waitForTransform("/torso_1", "/head_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/head_1", ros::Time(0), tf_head);
			
			x_tmp = tf_head.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_head.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_head.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - middle2_x;
			y_diff = y_tmp - middle2_y;
			z_diff = z_tmp - middle2_z;

			middle2_x = x_tmp;  
			middle2_y = y_tmp;
			middle2_z = z_tmp;

			//putting the values in vector to save

			head_x.push_back(x_diff);
			head_y.push_back(y_diff);
			head_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_head.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_head=tf_head.getRotation();

                        head_roll.push_back(x_diff);
                        head_pitch.push_back(y_diff);
                        head_yaw.push_back(z_diff);

			cout <<"HEAD VALUE PUSHED INTO VECTOR" <<endl;

// ---------- FOR THE TORSO ---------------------------------------------------------------
			
			listener.waitForTransform("/openni_depth_frame", "/torso_1", now, ros::Duration(0.3) );
                        listener.lookupTransform("/openni_depth_frame", "/torso_1", ros::Time(0),tf_torso);

			x_tmp = tf_torso.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			y_tmp = tf_torso.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			z_tmp = tf_torso.getOrigin().z();
			
			// the difference between current and previous position 
			x_diff = x_tmp - middle3_x;
			y_diff = y_tmp - middle3_y;
			z_diff = z_tmp - middle3_z;

			middle3_x = x_tmp;  
			middle3_y = y_tmp;
			middle3_z = z_tmp;

			//putting the values in vector to save

			torso_x.push_back(x_diff);
			torso_y.push_back(y_diff);
			torso_z.push_back(z_diff);
			
			//double right_hand_roll,right_hand_pitch, right_hand_yaw;          // compute rotations
                        tf_torso.getBasis().getRPY(x_diff,y_diff,z_diff);
                        tf::Quaternion q_torso=tf_torso.getRotation();

                        torso_roll.push_back(x_diff);
                        torso_pitch.push_back(y_diff);
                        torso_yaw.push_back(z_diff);

			cout <<"TORSO VALUE PUSHED INTO VECTOR" <<endl;

		}
		catch (tf::TransformException ex){
			ROS_ERROR("%s",ex.what());
		}
		rate.sleep();
		cout << "iteration:   "<< loop<<endl; 
	}
	





    cout <<"ITERATOR STARS NOW, PLEASE PAY ATTENTION"<<endl;
    ofstream x_file;

    vector<double>::iterator iy = right_hand_y.begin();
    vector<double>::iterator iz = right_hand_z.begin();
    
    vector<double>::iterator ir = right_hand_roll.begin();   
    vector<double>::iterator ip = right_hand_pitch.begin();
    vector<double>::iterator iw = right_hand_yaw.begin(); 

    
    vector<double>::iterator jx = left_hand_x.begin();    vector<double>::iterator jr = left_hand_roll.begin();
    vector<double>::iterator jy = left_hand_y.begin();    vector<double>::iterator jp = left_hand_pitch.begin();
    vector<double>::iterator jz = left_hand_z.begin();    vector<double>::iterator jw = left_hand_yaw.begin();

    vector<double>::iterator kx = right_elbow_x.begin();  vector<double>::iterator kr = right_elbow_roll.begin();
    vector<double>::iterator ky = right_elbow_y.begin();  vector<double>::iterator kp = right_elbow_pitch.begin();
    vector<double>::iterator kz = right_elbow_z.begin();  vector<double>::iterator kw = right_elbow_yaw.begin();

    vector<double>::iterator lx = left_elbow_x.begin();   vector<double>::iterator lr = left_elbow_roll.begin();
    vector<double>::iterator ly = left_elbow_y.begin();   vector<double>::iterator lp = left_elbow_pitch.begin();
    vector<double>::iterator lz = left_elbow_z.begin();   vector<double>::iterator lw = left_elbow_yaw.begin();
    
    vector<double>::iterator mx = head_x.begin();    vector<double>::iterator mr = head_roll.begin();
    vector<double>::iterator my = head_y.begin();    vector<double>::iterator mp = head_pitch.begin();
    vector<double>::iterator mz = head_z.begin();    vector<double>::iterator mw = head_yaw.begin();

    vector<double>::iterator nx = neck_x.begin();    vector<double>::iterator nr = neck_roll.begin();
    vector<double>::iterator ny = neck_y.begin();    vector<double>::iterator np = neck_pitch.begin();
    vector<double>::iterator nz = neck_z.begin();    vector<double>::iterator nw = neck_yaw.begin();

    vector<double>::iterator px = left_shoulder_x.begin();   vector<double>::iterator pr = left_shoulder_roll.begin();
    vector<double>::iterator py = left_shoulder_y.begin();   vector<double>::iterator pp = left_shoulder_pitch.begin();
    vector<double>::iterator pz = left_shoulder_z.begin();   vector<double>::iterator pw = left_shoulder_yaw.begin();
 
    vector<double>::iterator qx = right_shoulder_x.begin();  vector<double>::iterator qr = right_shoulder_roll.begin();
    vector<double>::iterator qy = right_shoulder_y.begin();  vector<double>::iterator qp = right_shoulder_pitch.begin();
    vector<double>::iterator qz = right_shoulder_z.begin();  vector<double>::iterator qw = right_shoulder_yaw.begin();

    vector<double>::iterator ox = torso_x.begin();  vector<double>::iterator orr = torso_roll.begin();
    vector<double>::iterator oy = torso_y.begin();  vector<double>::iterator op = torso_pitch.begin();
    vector<double>::iterator oz = torso_z.begin();  vector<double>::iterator ow = torso_yaw.begin();

/*
    x_file.open ("legbye_June16.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 4;    // first entry in the row will be label
		x_file << ",";
*/

if(strcmp(argv[1],"Stop")==0)
   { x_file.open ("STOP.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 1;
		x_file << ",";
	}

 if(strcmp(argv[1],"Call")==0) 
   { x_file.open ("Call.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 2;
		x_file << ",";
	}

if(strcmp(argv[1],"Hello")==0) 
   { x_file.open ("Hello.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 3;
		x_file << ",";
	}

if(strcmp(argv[1],"Coming")==0) 
   { x_file.open ("Coming.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 4;
	    x_file << ",";
	}

if(strcmp(argv[1],"Going")==0) 
   { x_file.open ("Going.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 5;
		x_file << ",";
	}

if(strcmp(argv[1],"Pointing")==0) 
   { x_file.open ("Pointing.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 6;
		x_file << ",";
	}

if(strcmp(argv[1],"Test")==0) 
   { x_file.open ("Test.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 0;
		x_file << ",";
	}

    for (vector<double>::iterator ix = right_hand_x.begin(); ix != right_hand_x.begin()+taille;++ix){
		//cout << *i << endl;
		x_file << *ix;
		x_file << ",";
		
		x_file << *iy;
		x_file << ",";
		iy++;
		
		x_file << *iz;
		x_file << ",";
		iz++;
		
                x_file << *ir;
		x_file << ",";
		ir++;
		
                x_file << *ip;
		x_file << ",";
		ip++;
		
                x_file << *iw;
		x_file << ",";
		iw++;

                x_file << *jx;
		x_file << ",";
		jx++;

                x_file << *jy;
		x_file << ",";
		jy++;

                x_file << *jz;
		x_file << ",";
		jz++;

                x_file << *jr;
		x_file << ",";
		jr++;

                x_file << *jp;
		x_file << ",";
		jp++;

                x_file << *jw;
		x_file << ",";
		jw++;

		x_file << *ox;
		x_file << ",";
		ox++;

                x_file << *oy;
		x_file << ",";
		oy++;

                x_file << *oz;
		x_file << ",";
		oz++;

                x_file << *orr;
		x_file << ",";
		orr++;

                x_file << *op;
		x_file << ",";
		op++;

                x_file << *ow;
		x_file << ",";
		ow++;

                x_file << *kx;
		x_file << ",";
		kx++;

                x_file << *ky;
		x_file << ",";
		ky++;

                x_file << *kz;
		x_file << ",";
		kz++;

                x_file << *kr;
		x_file << ",";
		kr++;

                x_file << *kp;
		x_file << ",";
		kp++;

                x_file << *kw;
		x_file << ",";
		kw++;

                x_file << *lx;
		x_file << ",";
		lx++;

                x_file << *ly;
		x_file << ",";
		ly++;

                x_file << *lz;
		x_file << ",";
		lz++;

                x_file << *lr;
		x_file << ",";
		lr++;

                x_file << *lp;
		x_file << ",";
		lp++;

                x_file << *lw;
		x_file << ",";
		lw++;

                x_file << *mx;
		x_file << ",";
		mx++;

                x_file << *my;
		x_file << ",";
		my++;

                x_file << *mz;
		x_file << ",";
		mz++;

                x_file << *mr;
		x_file << ",";
		mr++;

                x_file << *mp;
		x_file << ",";
		mp++;

                x_file << *mw;
		x_file << ",";
		mw++;

                x_file << *nx;
		x_file << ",";
		nx++;

                x_file << *ny;
		x_file << ",";
		ny++;

                x_file << *nz;
		x_file << ",";
		nz++;

                x_file << *nr;
		x_file << ",";
		nr++;

                x_file << *np;
		x_file << ",";
		np++;

                x_file << *nw;
		x_file << ",";
		nw++;

                x_file << *px;
		x_file << ",";
		px++;

                x_file << *py;
		x_file << ",";
		py++;

                x_file << *pz;
		x_file << ",";
		pz++;

                x_file << *pr;
		x_file << ",";
		pr++;

                x_file << *pp;
		x_file << ",";
		pp++;

                x_file << *pw;
		x_file << ",";
		pw++;

                x_file << *qx;
		x_file << ",";
		qx++;

                x_file << *qy;
		x_file << ",";
		qy++;

                x_file << *qz;
		x_file << ",";
		qz++;

                x_file << *qr;
		x_file << ",";
		qr++;

                x_file << *qp;
		x_file << ",";
		qp++;

                x_file << *qw;
		x_file << ",";
		qw++;
		
				
    }
   //x_file << 0;
    x_file << "\n";
/*    
    cout <<"Y VALUES TARTS NOW. KEEP IN MIND"<<endl;
    for (vector<double>::iterator i = right_hand_y.begin(); i != right_hand_y.end();++i){
		cout << *i << endl;
		x_file << *i;
		x_file << ",";
	}
    x_file << "\n";
    
    cout <<"Z VALUES TARTS NOW. KEEP IN MIND"<<endl;
    
    for (vector<double>::iterator i = right_hand_z.begin(); i != right_hand_z.end();++i){
		cout << *i << endl;
		x_file << *i;
		x_file << ",";
    }
    x_file << "\n";
     
*/
    x_file.close();

	return 0;
};

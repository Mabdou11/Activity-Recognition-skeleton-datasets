#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <stdio.h>
#include <fstream>
#include <openni_tracker_SVM/msg_SVM.h>
#include <std_msgs/Float64.h>


using namespace std;
#define PI 3.14159265
#define taille 3


/*  ros::Publisher pub;
ros::Subscriber sub;

float qx,qy,qz,qw; 
    double sqw;    
    double sqx;    
    double sqy;    
    double sqz; 
    
         vector<double> pose_x;
         vector<double> pose_y;
         vector<double> pose_z;
         
      float  pose_z_tmp, pose_x_tmp, pose_y_tmp;

 void pos_orientation(const openni_tracker_SVM::msg_SVM::ConstPtr& msg)
{  
         ros::NodeHandle h1;
         std_msgs::Float64  angle;
        // ros::Publisher pub;
         pub= h1.advertise<std_msgs::Float64>("orientation",1);
       
         qx=msg->qx;
         qy=msg->qy;
         qz=msg->qz;
         qw=msg->qw;
  
    sqw = qw*qw;    
    sqx = qx*qx;    
    sqy = qy*qy;    
    sqz = qz*qz; 

    pose_x_tmp =  (atan2(2.0 * (qy*qz + qx*qw),(-sqx - sqy + sqz + sqw)) * (180.0f/PI));          
    pose_y_tmp =  (asin(-2.0 * (qx*qz - qy*qw)) * (180.0f/PI));
    pose_z_tmp =  (atan2(2.0 * (qx*qy + qz*qw),(sqx - sqy - sqz + sqw)) * (180.0f/PI));
   // angle.data= pose_z_tmp;
  // cout << "pose_z_tmp "<< pose_z_tmp <<endl;
   //cout << "qx "<< qx <<endl;
  pose_x.push_back(pose_x_tmp);
  pose_y.push_back(pose_y_tmp);
  pose_z.push_back(pose_z_tmp);
cout <<"POSE PUSHED INTO VECTOR" <<endl;

//if (pose_z_tmp<30 && pose_z_tmp >-30) cout<<"La Pose de l'utilisateur est  : Face !!" << pose_z_tmp <<endl;
    
//if(pose_z_tmp>=30 && pose_z_tmp<150) cout<<"La Pose de l'utilisateur est  : Droite !!"<< pose_z_tmp <<endl;   

//if(pose_z_tmp<-30 && pose_z_tmp-150) cout<<"La Pose de l'utilisateur est  : Gauche !!"<< pose_z_tmp<<endl;

//if(pose_z_tmp>=150 ) cout<<"La Pose de l'utilisateur est  : Dos !!"<< pose_z_tmp <<endl;
   
//if (pose_z_tmp<=-150) cout<<"La Pose de l'utilisateur est  : Dos !!"<< pose_z_tmp <<endl;  

 
pub.publish(angle);
  
  }*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv){
	
	ros::init(argc, argv, "my_tf_listener");
	ros::NodeHandle node,h2;
	tf::TransformListener listener;

	ros::Rate rate(30.0);
        float frame_rate=1/30.0;

	vector<double> right_hand_x;
	vector<double> right_hand_y;
	vector<double> right_hand_z;

	vector<double> left_hand_x;
	vector<double> left_hand_y;
	vector<double> left_hand_z;

        vector<double> right_shoulder_x;
	vector<double> right_shoulder_y;
	vector<double> right_shoulder_z;

        vector<double> left_shoulder_x;
	vector<double> left_shoulder_y;
	vector<double> left_shoulder_z;

        vector<double> right_elbow_x;
	vector<double> right_elbow_y;
	vector<double> right_elbow_z;

        vector<double> left_elbow_x;
	vector<double> left_elbow_y;
	vector<double> left_elbow_z;


	vector<double> head_x;
	vector<double> head_y;
	vector<double> head_z;
  
    double right_x = 0;  
    double right_y = 0;
    double right_z = 0;

    double left_x = 0;  
    double left_y = 0;
    double left_z = 0;

    double right1_x = 0;  
    double right1_y = 0;
    double right1_z = 0;

    double left1_x = 0;  
    double left1_y = 0;
    double left1_z = 0;

    double right2_x = 0;  
    double right2_y = 0;
    double right2_z = 0;

    double left2_x = 0;  
    double left2_y = 0;
    double left2_z = 0;


    double head1_x = 0;  
    double head1_y = 0;
    double head1_z = 0;


///////////////////////////////////// Compute orientation///////////////////////////////////////////////

       //  sub = h2.subscribe("pos",1, &pos_orientation);
        
        
///////////////////////////////////////////////////////////////////////////////////////////////////////

int loop=0;

	while (node.ok()){
            //    ros::spinOnce();
		tf::StampedTransform transform1;
		tf::StampedTransform transform2;
                tf::StampedTransform transform3;
                tf::StampedTransform transform4;
                tf::StampedTransform transform5;
                tf::StampedTransform transform6;
                tf::StampedTransform transform7;

                 ros::Duration timeout(1.0 / 30);
                 ros::Time now = ros::Time(0);//now();
		try{
			
// ---------- FOR THE RIGHT HAND ---------------------------------------------------------------
			listener.waitForTransform("/torso_1", "/right_hand_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/right_hand_1", ros::Time(0), transform1);

			double right_x_tmp = transform1.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double right_y_tmp = transform1.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double right_z_tmp = transform1.getOrigin().z();
			
			// the difference between current and previous position 
			double right_x_diff = right_x_tmp - right_x;
			double right_y_diff = right_y_tmp - right_y;
			double right_z_diff = right_z_tmp - right_z;

			right_x = right_x_tmp;  
			right_y = right_y_tmp;
			right_z = right_z_tmp;

			//putting the values in vector to save

			right_hand_x.push_back(right_x_diff);
			right_hand_y.push_back(right_y_diff);
			right_hand_z.push_back(right_z_diff);
			
			cout <<"RIGHT HAND VALUE PUSHED INTO VECTOR" <<endl;

// --------------------- FOR THE LEFT HAND ------------------------------------------------------			
			listener.waitForTransform("/torso_1", "/left_hand_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/left_hand_1", ros::Time(0), transform2);
			
			double left_x_tmp = transform2.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double left_y_tmp = transform2.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double left_z_tmp = transform2.getOrigin().z();

			// the difference between current and previous position 
			double left_x_diff = left_x_tmp - left_x;
			double left_y_diff = left_y_tmp - left_y;
			double left_z_diff = left_z_tmp - left_z;

			left_x = left_x_tmp;  
			left_y = left_y_tmp;
			left_z = left_z_tmp;

//putting the values in vector to save

			left_hand_x.push_back(left_x_diff);
			left_hand_y.push_back(left_y_diff);
			left_hand_z.push_back(left_z_diff);

        cout <<"Left hand VALUE PUSHED INTO VECTOR" <<endl;


// --------------------- FOR THE right shoulder ------------------------------------------------------			
			listener.waitForTransform("/torso_1", "/right_shoulder_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/right_shoulder_1", ros::Time(0), transform3);
			
			double right1_x_tmp = transform3.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double right1_y_tmp = transform3.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double right1_z_tmp = transform3.getOrigin().z();

			// the difference between current and previous position 
			double right1_x_diff = right1_x_tmp - right1_x;
			double right1_y_diff = right1_y_tmp - right1_y;
			double right1_z_diff = right1_z_tmp - right1_z;

			right1_x = right1_x_tmp;  
			right1_y = right1_y_tmp;
			right1_z = right1_z_tmp;

//putting the values in vector to save

			right_shoulder_x.push_back(right1_x_diff);
			right_shoulder_y.push_back(right1_y_diff);
			right_shoulder_z.push_back(right1_z_diff);

			cout <<"Right shoulder VALUE PUSHED INTO VECTOR" <<endl;

// ------------------------------for left shoulder---------------------------------------------			
			listener.waitForTransform("/torso_1", "/left_shoulder_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/left_shoulder_1", ros::Time(0), transform4);
			
			double left1_x_tmp = transform4.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double left1_y_tmp = transform4.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double left1_z_tmp = transform4.getOrigin().z();

			// the difference between current and previous position 
			double left1_x_diff = left1_x_tmp - left1_x;
			double left1_y_diff = left1_y_tmp - left1_y;
			double left1_z_diff = left1_z_tmp - left1_z;

			left1_x = left1_x_tmp;  
			left1_y = left1_y_tmp;
			left1_z = left1_z_tmp;

//putting the values in vector to save

			left_shoulder_x.push_back(left1_x_diff);
			left_shoulder_y.push_back(left1_y_diff);
			left_shoulder_z.push_back(left1_z_diff);


			cout <<"LEFT shoulder VALUE PUSHED INTO VECTOR" <<endl;

// ------------------------------for left elbow---------------------------------------------			
			listener.waitForTransform("/torso_1", "/left_elbow_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/left_elbow_1", ros::Time(0), transform6);
			
			double left2_x_tmp = transform6.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double left2_y_tmp = transform6.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double left2_z_tmp = transform6.getOrigin().z();

			// the difference between current and previous position 
			double left2_x_diff = left2_x_tmp - left2_x;
			double left2_y_diff = left2_y_tmp - left2_y;
			double left2_z_diff = left2_z_tmp - left2_z;

			left2_x = left2_x_tmp;  
			left2_y = left2_y_tmp;
			left2_z = left2_z_tmp;

//putting the values in vector to save

			left_elbow_x.push_back(left2_x_diff);
			left_elbow_y.push_back(left2_y_diff);
			left_elbow_z.push_back(left2_z_diff);

			cout <<"LEFT shoulder VALUE PUSHED INTO VECTOR" <<endl;

// ------------------------------for right elbow---------------------------------------------			
			listener.waitForTransform("/torso_1", "/right_elbow_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/right_elbow_1", ros::Time(0), transform7);
			
			double right2_x_tmp = transform7.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double right2_y_tmp = transform7.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double right2_z_tmp = transform7.getOrigin().z();

			// the difference between current and previous position 
			double right2_x_diff = right2_x_tmp - right2_x;
			double right2_y_diff = right2_y_tmp - right2_y;
			double right2_z_diff = right2_z_tmp - right2_z;

			right2_x = right2_x_tmp;  
			right2_y = right2_y_tmp;
			right2_z = right2_z_tmp;

//putting the values in vector to save

			right_elbow_x.push_back(right2_x_diff);
			right_elbow_y.push_back(right2_y_diff);
			right_elbow_z.push_back(right2_z_diff);

			cout <<"right shoulder VALUE PUSHED INTO VECTOR" <<endl;



//////////////////////////////////////////////Head ////////////////////////////////////////////////////////////
			
                        listener.waitForTransform("/torso_1", "/head_1", now, ros::Duration(0.3) );
			listener.lookupTransform("/torso_1", "/head_1", ros::Time(0), transform5);
			
			double head_x_tmp = transform5.getOrigin().x();  // returns a position of the joint with respect to fixed frame 
			double head_y_tmp = transform5.getOrigin().y();  // individual elements of position can be accessed by x,y,z
			double head_z_tmp = transform5.getOrigin().z();

			// the difference between current and previous position 
			double head_x_diff = head_x_tmp - head1_x;
			double head_y_diff = head_y_tmp - head1_y;
			double head_z_diff = head_z_tmp - head1_z;

			head1_x = head_x_tmp;  
			head1_y = head_y_tmp;
			head1_z = head_z_tmp;

//putting the values in vector to save

			head_x.push_back(head_x_diff);
			head_y.push_back(head_y_diff);
			head_z.push_back(head_z_diff);

			cout <<"HEAD VALUE PUSHED INTO VECTOR" <<endl;

		}
		catch (tf::TransformException ex){
			ROS_ERROR("%s",ex.what());
		}
		 ros::Duration(1).sleep(); //0.5 second;
        cout<<"frame  "<<loop<<endl;
        loop++;
	}
	
    cout <<"ITERATOR STARS NOW, PLEASE PAY ATTENTION"<<endl;
    ofstream x_file;
    vector<double>::iterator j = right_hand_y.begin();
    vector<double>::iterator k = right_hand_z.begin();  
    
    vector<double>::iterator l = left_hand_x.begin();
    vector<double>::iterator m = left_hand_y.begin();
    vector<double>::iterator n = left_hand_z.begin();

    vector<double>::iterator o = right_shoulder_x.begin();
    vector<double>::iterator p = right_shoulder_y.begin();
    vector<double>::iterator q = right_shoulder_z.begin();

    vector<double>::iterator r = left_shoulder_x.begin();
    vector<double>::iterator s = left_shoulder_y.begin();
    vector<double>::iterator t = left_shoulder_z.begin();

    vector<double>::iterator u = head_x.begin();
    vector<double>::iterator v = head_y.begin();
    vector<double>::iterator w = head_z.begin();

    vector<double>::iterator x = right_elbow_x.begin();
    vector<double>::iterator y = right_elbow_y.begin();
    vector<double>::iterator z = right_elbow_z.begin();

    vector<double>::iterator e = left_elbow_x.begin();
    vector<double>::iterator f = left_elbow_y.begin();
    vector<double>::iterator g = left_elbow_z.begin();


   if(strcmp(argv[1],"Stop")==0)
   { x_file.open ("STOP_selectedPos.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 1;
		x_file << ",";
	}

 if(strcmp(argv[1],"Call")==0) 
   { x_file.open ("Call_selectedPos.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 2;
		x_file << ",";
	}

if(strcmp(argv[1],"No")==0) 
   { x_file.open ("No_slectedPos.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 3;
		x_file << ",";
	}

if(strcmp(argv[1],"Yes")==0) 
   { x_file.open ("Yes_All.csv", ios::app); //the flag ios::app makes sure that the control starts at the end of already existing file.
		x_file << 4;
	    x_file << ",";
	}


    for (vector<double>::iterator i = right_hand_x.begin(); i != right_hand_x.begin()+10;++i){
		
            /*RH*/
                cout << *i << endl;
		x_file << *i;
		x_file << ",";
		
		x_file << *j;
		x_file << ",";
		j++;
		
		x_file << *k;
		x_file << ",";
		k++;
	      /*LH*/	
		x_file << *l;
		x_file << ",";
		l++;		
		
		x_file << *m;
		x_file << ",";
		m++;		
		
		x_file << *n;
		x_file << ",";
		n++;
		/*RS*/		
		x_file << *o;
		x_file << ",";
		o++;				
		
		x_file << *p;
		x_file << ",";
		p++;				
		
		x_file << *q;
		x_file << ",";
		q++;	
              /*LS*/  
               /* x_file << *r;
		x_file << ",";
		r++;

                x_file << *s;
		x_file << ",";
		s++;*/

                x_file << *t;
		x_file << ",";
		t++;
               /*H*/
               /* x_file << *u;
		x_file << ",";
		u++;
 
                x_file << *v;
		x_file << ",";
		v++;*/
 
                x_file << *w;
		x_file << ",";
		w++;	
           /*RE*/
                x_file << *x;
		x_file << ",";
		x++;
 
                x_file << *y;
		x_file << ",";
		y++;
 
                x_file << *z;
		x_file << ",";
		z++;	
          /*LE*/		
		x_file << *e;
		x_file << ",";
		e++;
 
                x_file << *f;
		x_file << ",";
		f++;
 
                x_file << *g;
		x_file << ",";
		g++;			
    }
    cout <<"nombre d'attributs Right hand:" << right_hand_x.size() << endl;
    cout <<"nombre d'attributs Left hand:" << right_hand_x.size() << endl;
    cout <<"nombre d'attributs head:" << right_hand_x.size() << endl;
  //  cout <<"nombre d'attributs pose:" << pose_z.size() << endl;
     

    x_file << 0;
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

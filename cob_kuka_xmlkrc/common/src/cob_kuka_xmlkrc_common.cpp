//ROS typedefs
#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/PoseStamped.h>
#include <cob_srvs/Trigger.h>
#include <cob_srvs/Trigger.h>
#include <cob_kuka_xmlkrc/KukaEthernetClient.h>

/* protected region user include files on begin */
int currentMsgID;
	clock_t start, finish;
   void testCallback(int msgID)
    {
    	std::cout << "Called back with MsgID: " << msgID << std::endl;
    	if (msgID == currentMsgID)
    	{
    		finish = clock();
    		cout << "Time needed:" << ( (finish - start)/CLOCKS_PER_SEC ) << endl;
    	}
    }
/* protected region user include files end */

class cob_kuka_xmlkrc_config
{
public:
		std::string KRC_ip_address;
		int KRC_ip_port;

};

class cob_kuka_xmlkrc_data
{
// autogenerated: don't touch this class
public:
//input data
  
	
//output data
    	sensor_msgs::JointState out_joint_states;
    	geometry_msgs::PoseStamped out_cart_pose;
 

};

class cob_kuka_xmlkrc_impl
{
	/* protected region user member variables on begin */
	KukaEthernetClient kuka_client_;
	/* protected region user member variables end */

public:
    cob_kuka_xmlkrc_impl() 
    {
        /* protected region user constructor on begin */
		/* protected region user constructor end */
    }
    void configure(cob_kuka_xmlkrc_config config) 
    {
        /* protected region user configure on begin */
    	std::cout << "Connecting to KUKA KRC on " << config.KRC_ip_address << ":" << config.KRC_ip_port << "\n";
    	//kuka_client_.Initialize("common/files/EKIServerFrame.xml", SocketAddress(config.KRC_ip_address, config.KRC_ip_port));
    	kuka_client_.Initialize("common/files/EKIServerFrame.xml", SocketAddress("192.1.10.20", 49152));
    	kuka_client_.setCallbackFcn(testCallback);

    	//actual moving the robot
    	//kuka_client_.movePTP(currentMsgID, KukaAxis(-33, -113, 100, 0, 100, 11), 10);// oben



		/* protected region user configure end */
    }
    void update(cob_kuka_xmlkrc_data &data, cob_kuka_xmlkrc_config config)
    {
        /* protected region user update on begin */

    	//dummy command to just get cartesian pose
    	//only do this if the robot is not moving
    	/*std::cout << "Asking for current position\n";
    	kuka_client_.addMessage(currentMsgID, SubID::EchoTest);
    	sleep(2.0);
    	KukaFrame currentframe = kuka_client_.getCurrentFrame();
    	std::cout << "hurray " << currentframe.toString() << "\n";
    	data.out_cart_pose.pose.position.x = currentframe.a[0]/1000;
    	data.out_cart_pose.pose.position.y = currentframe.a[1]/1000;
    	data.out_cart_pose.pose.position.z = currentframe.a[2]/1000;*/
		/* protected region user update end */
    }


	bool callback_Init(cob_srvs::Trigger::Request  &req, cob_srvs::Trigger::Response &res , cob_kuka_xmlkrc_config config)
	{
		/* protected region user implementation of service callback for Init on begin */
		std::cout << config.KRC_ip_port << "\n";

		/* protected region user implementation of service callback for Init end */
		return true;
	}
	bool callback_MoveLin_BL(cob_srvs::Trigger::Request  &req, cob_srvs::Trigger::Response &res , cob_kuka_xmlkrc_config config)
	{
		/* protected region user implementation of service callback for MoveLin_BL on begin */
		kuka_client_.moveLIN(5, KukaFrame(735,177,443,170,1,179), 0.5);
		/* protected region user implementation of service callback for MoveLin_BL end */
		return true;
	}
    
    /* protected region user additional functions on begin */
	/* protected region user additional functions end */
    
};

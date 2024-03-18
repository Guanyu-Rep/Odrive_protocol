#include <string>
#include "common_inc.h"


void OnUsbAsciiCmd(const char* _cmd, size_t _len, StreamSink &_responseChannel)
{
    /*---------------------------- ↓ Add Your CMDs Here ↓ -----------------------------*/
    if (_cmd[0] == '!')
    {
        LED_B_TogglePin;
    }

/*---------------------------- ↑ Add Your CMDs Here ↑ -----------------------------*/
}


void OnUart1AsciiCmd(const char* _cmd, size_t _len, StreamSink &_responseChannel)
{
    /*---------------------------- ↓ Add Your CMDs Here ↓ -----------------------------*/
    if (_cmd[0] == '!')
    {
        LED_B_TogglePin;
        Respond(*uart1StreamOutputPtr, "[sys] ENTER CMD UART1\n");
    }else{
        Respond(*uart1StreamOutputPtr, "[sys] ENTER CMD UART1 with error cmd\n");
    }
//    if (_cmd[0] == '!' || !dummy.IsEnabled())
//    {
//        std::string s(_cmd);
//        if (s.find("STOP") != std::string::npos)
//        {
//            dummy.commandHandler.EmergencyStop();
//            Respond(_responseChannel, "Stopped ok");
//        } else if (s.find("START") != std::string::npos)
//        {
//            dummy.SetEnable(true);
//            Respond(_responseChannel, "Started ok");
//        } else if (s.find("DISABLE") != std::string::npos)
//        {
//            dummy.SetEnable(false);
//            Respond(_responseChannel, "Disabled ok");
//        }
//    } else if (_cmd[0] == '#')
//    {
//        std::string s(_cmd);
//        if (s.find("GETJPOS") != std::string::npos)
//        {
//            Respond(_responseChannel, "ok %.2f %.2f %.2f %.2f %.2f %.2f",
//                    dummy.currentJoints.a[0], dummy.currentJoints.a[1],
//                    dummy.currentJoints.a[2], dummy.currentJoints.a[3],
//                    dummy.currentJoints.a[4], dummy.currentJoints.a[5]);
//        } else if (s.find("GETLPOS") != std::string::npos)
//        {
//            dummy.UpdateJointPose6D();
//            Respond(_responseChannel, "ok %.2f %.2f %.2f %.2f %.2f %.2f",
//                    dummy.currentPose6D.X, dummy.currentPose6D.Y,
//                    dummy.currentPose6D.Z, dummy.currentPose6D.A,
//                    dummy.currentPose6D.B, dummy.currentPose6D.C);
//        } else if (s.find("CMDMODE") != std::string::npos)
//        {
//            uint32_t mode;
//            sscanf(_cmd, "#CMDMODE %lu", &mode);
//            dummy.SetCommandMode(mode);
//            Respond(_responseChannel, "Set command mode to [%lu]", mode);
//        } else
//            Respond(_responseChannel, "ok");
//    } else if (_cmd[0] == '>' || _cmd[0] == '@')
//    {
//        uint32_t freeSize = dummy.commandHandler.Push(_cmd);
//        Respond(_responseChannel, "%d", freeSize);
//    }
/*---------------------------- ↑ Add Your CMDs Here ↑ -----------------------------*/
}


void OnUart2AsciiCmd(const char* _cmd, size_t _len, StreamSink &_responseChannel)
{
    /*---------------------------- ↓ Add Your CMDs Here ↓ -----------------------------*/
    if (_cmd[0] == '!')
    {
        LED_B_TogglePin;
    }

/*---------------------------- ↑ Add Your CMDs Here ↑ -----------------------------*/
}
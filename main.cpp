#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unistd.h>

using namespace std;

struct EventData_WindowResize
{
    int Width;
    int Height;
};
struct EventData_KeyInput
{
    int Key;
    int Scancode;
    int Action;
    int Modifier;
};
struct EventData_MouseMove
{
    double PosX; 
    double PosY;
};
struct EventData_MouseButton
{
    int Button; 
    int Action; 
    int Modifier;
};
struct EventData_MouseScroll
{
    double OffsetX; 
    double OffsetY;
};
   
// EventDispatcher singleton
template<typename T_Data>
class EventDispatcher
{
public:
    static void RegisterHandler(const function<void(T_Data data)>& eventHandler)
    {
        get().m_EventHandlers.push_back(eventHandler);
    }
    static void Dispatch(T_Data newEvent) 
    {        
        for(const function<void(T_Data)>& eventHandler : get().m_EventHandlers) {
            eventHandler(newEvent);
        }
    }
private:
    vector<function<void(T_Data)>> m_EventHandlers;
    
    static EventDispatcher& get() 
    {
		static EventDispatcher instance;
        return instance;
    }
    // delete constructor / copy constructor / assignment operator
    EventDispatcher() {}
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator= (const EventDispatcher&) = delete;
};


int main()
{
    auto WindowResize1 = [](EventData_WindowResize data) {
        cout << "WindowResize 1: x = " << data.Width<< " y = " << data.Height<< endl;
    };
    auto WindowResize2 = [](EventData_WindowResize data) {
        cout << "WindowResize 2: x = " << data.Width << " y = " << data.Height<< endl;
    };

    EventDispatcher<EventData_WindowResize>::RegisterHandler(WindowResize1);
    EventDispatcher<EventData_WindowResize>::RegisterHandler(WindowResize2);
    
    
    auto MouseMove1 = [](EventData_MouseMove data) {
        cout << "MouseMove 1: x = " << data.PosX << " y = " << data.PosY << endl;
    };
    auto MouseMove2 = [](EventData_MouseMove data) {
        cout << "MouseMove 2: x = " << data.PosX << " y = " << data.PosY << endl;
    };

    EventDispatcher<EventData_MouseMove>::RegisterHandler(MouseMove1);
    EventDispatcher<EventData_MouseMove>::RegisterHandler(MouseMove2);
    
    
    for (int i = 0; i < 10; i++)
    {
        EventData_MouseMove m_MouseData = { i*2.0, i*3.0 };
        EventDispatcher<EventData_MouseMove>::Dispatch(m_MouseData);
        
        EventData_WindowResize m_WindowData = { i*4, i*5 };
        EventDispatcher<EventData_WindowResize>::Dispatch(m_WindowData);
        
        sleep(1);
    }
    
    return 0;
}






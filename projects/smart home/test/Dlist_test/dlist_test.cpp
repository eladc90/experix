#include <iostream> 
#include "distributaion_list.hpp"
#include "mu_test.h"
#include "controller_agent.hpp"
#include "type.hpp"
#include "location.hpp"

using namespace smartHome;

typedef std::string EventType;
typedef std::string Id;

SharedPtr<ControllerAgent> MakeController(Type a_eventType, Location a_location, std::string a_id) {
    static unsigned int runningNum = 0;
    ++runningNum;
    return SharedPtr<ControllerAgent>( new ControllerAgent(a_id, a_eventType.GetType(),
                                        "log", a_location.GetRoom(), a_location.GetFloor()));     
}

void SendToList(SubcriberList& a_list , SharedPtr<Event> a_event) {
    SubcriberListItr begin = a_list.BeginItr();
    SubcriberListItr end = a_list.EndItr();
    while (begin != end) {
        (*begin)->HandleEvent(a_event);
        ++begin;
    }
}

UNIT(controller_1) 
    //initialize 
    DistributionList dlist;
    Type fireType("fire");
    Location allFireInFloor("*", "*");
    Location room("1", "2");
    Id id("1");
    ID eventId("1");
    SharedPtr<Event> event(new Event(eventId, fireType, room));
    SharedPtr<ControllerAgent> fireController = MakeController(fireType, allFireInFloor, id);
    dlist.AddController(fireController, fireType, allFireInFloor);

    //start
    SubcriberList subList = dlist.GetMailListByEvent(event);
    SubcriberListItr begin = subList.BeginItr();
    SubcriberListItr end = subList.EndItr();
    while (begin != end) {
        (*begin)->HandleEvent(event);
        ++begin;
    }

    //test
    ASSERT_EQUAL(fireController->GetNumOfEventsRecived() ,1);
END_UNIT

UNIT(controller_2) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type fireType("fire");
    Location allFireInFloor("*", "1");
    Location FireInRoom("9", "1");
    SharedPtr<ControllerAgent> fireFloorController = MakeController(fireType, allFireInFloor, "1");
    SharedPtr<ControllerAgent> fireRoomController = MakeController(fireType, FireInRoom, "2");

    //events
    Location room("9", "1");
    Location roomForTheFloor("4", "1");
    ID firstEvent("1");
    ID secEvent("1");
    ID eventId("1");
    SharedPtr<Event> event(new Event(firstEvent, fireType, room));
    SharedPtr<Event> eventNoRoom(new Event(secEvent, fireType, roomForTheFloor));

    dlist.AddController(fireFloorController, fireType, allFireInFloor);
    dlist.AddController(fireRoomController, fireType, FireInRoom);

    //start
    SubcriberList subList = dlist.GetMailListByEvent(event);
    SubcriberList subListNoRoom = dlist.GetMailListByEvent(eventNoRoom);

    SendToList(subList, event);
    SendToList(subListNoRoom, eventNoRoom);

    //test
    ASSERT_EQUAL(fireFloorController->GetNumOfEventsRecived() ,2);
    ASSERT_EQUAL(fireRoomController->GetNumOfEventsRecived() ,1);
END_UNIT


UNIT(controller_3) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type fireType("fire");
    Location allFireInBuilding("*", "*");
    Location allFireInFloor("*", "1");
    Location FireInRoom("9", "1");
    SharedPtr<ControllerAgent> fireBuildingController = MakeController(fireType, allFireInBuilding, "1");
    SharedPtr<ControllerAgent> fireFloorController = MakeController(fireType, allFireInFloor, "2");
    SharedPtr<ControllerAgent> fireRoomController = MakeController(fireType, FireInRoom, "3");

    //events
    Location room("9", "1");
    Location roomForTheFloor("4", "1");
    Location roomForTheBuilding("4", "3");
    ID firstEvent("1");
    ID secEvent("1");
    ID eventId("1");
    SharedPtr<Event> event(new Event(firstEvent, fireType, room));
    SharedPtr<Event> eventNoRoom(new Event(secEvent, fireType, roomForTheFloor));
    SharedPtr<Event> eventNoFloor(new Event(secEvent, fireType, roomForTheBuilding));

    dlist.AddController(fireFloorController, fireType, allFireInFloor);
    dlist.AddController(fireRoomController, fireType, FireInRoom);
    dlist.AddController(fireBuildingController, fireType, allFireInBuilding);

    //start
    SubcriberList subList = dlist.GetMailListByEvent(event);
    SubcriberList subListNoRoom = dlist.GetMailListByEvent(eventNoRoom);
    SubcriberList subListNoFloor = dlist.GetMailListByEvent(eventNoFloor);

    SendToList(subList, event);
    SendToList(subListNoRoom, eventNoRoom);
    SendToList(subListNoFloor, eventNoFloor);
    
    //test
    ASSERT_EQUAL(fireBuildingController->GetNumOfEventsRecived() ,3);
    ASSERT_EQUAL(fireFloorController->GetNumOfEventsRecived() ,2);
    ASSERT_EQUAL(fireRoomController->GetNumOfEventsRecived() ,1);
END_UNIT

UNIT(controller_5_no_overlap) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type fireType("fire");
    Type lightType("light");
    Location fireInRoomNum1("1", "1");
    Location fireInRoomNum2("2", "1");
    Location fireInRoomNum3("3", "1");
    Location lightInRoomNum1("1", "1");
    Location lightInRoomNum2("2", "1");

    SharedPtr<ControllerAgent> fireConRoomNum1 = MakeController(fireType, fireInRoomNum1, "1");
    SharedPtr<ControllerAgent> fireConRoomNum2 = MakeController(fireType, fireInRoomNum2, "2");
    SharedPtr<ControllerAgent> fireConRoomNum3 = MakeController(fireType, fireInRoomNum3, "3");
    
    SharedPtr<ControllerAgent> lightConRoomNum1 = MakeController(lightType, lightInRoomNum1, "1");
    SharedPtr<ControllerAgent> lightConRoomNum2 = MakeController(lightType, lightInRoomNum2, "2");

    //events
    ID eventId("1");
    SharedPtr<Event> EventfireInRoomNum1(new Event(eventId, fireType, fireInRoomNum1));
    SharedPtr<Event> EventfireInRoomNum2(new Event(eventId, fireType, fireInRoomNum2));
    SharedPtr<Event> EventfireInRoomNum3(new Event(eventId, fireType, fireInRoomNum3));
    SharedPtr<Event> EventLightInRoomNum1(new Event(eventId, lightType, lightInRoomNum1));
    SharedPtr<Event> EventLightInRoomNum2(new Event(eventId, lightType, lightInRoomNum2));


    dlist.AddController(fireConRoomNum1, fireType, fireInRoomNum1);
    dlist.AddController(fireConRoomNum2, fireType, fireInRoomNum2);
    dlist.AddController(fireConRoomNum3, fireType, fireInRoomNum3);

    dlist.AddController(lightConRoomNum1, lightType, lightInRoomNum1);
    dlist.AddController(lightConRoomNum2, lightType, lightInRoomNum2);

    //start
    SubcriberList lisrFireRoomNum1 = dlist.GetMailListByEvent(EventfireInRoomNum1);
    SubcriberList lisrFireRoomNum2 = dlist.GetMailListByEvent(EventfireInRoomNum2);
    SubcriberList lisrFireRoomNum3 = dlist.GetMailListByEvent(EventfireInRoomNum3);
    SubcriberList lisrLightRoomNum1 = dlist.GetMailListByEvent(EventLightInRoomNum1);
    SubcriberList lisrLightRoomNum2 = dlist.GetMailListByEvent(EventLightInRoomNum2);


    SendToList(lisrFireRoomNum1, EventfireInRoomNum1);
    SendToList(lisrFireRoomNum2, EventfireInRoomNum2);
    SendToList(lisrFireRoomNum3, EventfireInRoomNum3);

    SendToList(lisrLightRoomNum1, EventLightInRoomNum1);
    SendToList(lisrLightRoomNum2, EventLightInRoomNum2);

    //test
    ASSERT_EQUAL(fireConRoomNum1->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(fireConRoomNum2->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(fireConRoomNum3->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(lightConRoomNum1->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(lightConRoomNum2->GetNumOfEventsRecived() ,1);

END_UNIT

UNIT(controller_5_with_overlap) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type fireType("fire");
    Type lightType("light");
    Location fireInRoomNum1("1", "1");
    Location fireInRoomNum2("2", "1");
    Location fireInRoomNum3("3", "1");
    Location fireInWholeBuilding("*", "*");
    Location lightInRoomNum1("1", "1");
    Location lightInRoomNum2("2", "1");
    Location lightWholeFloor("*", "1");

    SharedPtr<ControllerAgent> fireConRoomNum1 = MakeController(fireType, fireInRoomNum1, "1");
    SharedPtr<ControllerAgent> fireConRoomNum2 = MakeController(fireType, fireInRoomNum2, "2");
    SharedPtr<ControllerAgent> fireContInWholeBuilding = MakeController(fireType, fireInWholeBuilding, "3");
    
    SharedPtr<ControllerAgent> lightConRoomNum1 = MakeController(lightType, lightInRoomNum1, "1");
    SharedPtr<ControllerAgent> lightConRoomNum2 = MakeController(lightType, lightWholeFloor, "2");

    //events
    ID eventId("1");
    SharedPtr<Event> EventfireInRoomNum1(new Event(eventId, fireType, fireInRoomNum1));
    SharedPtr<Event> EventfireInRoomNum2(new Event(eventId, fireType, fireInRoomNum2));
    SharedPtr<Event> EventfireInRoomNum3(new Event(eventId, fireType, fireInRoomNum3));
    SharedPtr<Event> EventLightInRoomNum1(new Event(eventId, lightType, lightInRoomNum1));
    SharedPtr<Event> EventLightInRoomNum2(new Event(eventId, lightType, lightInRoomNum2));


    dlist.AddController(fireConRoomNum1, fireType, fireInRoomNum1);
    dlist.AddController(fireConRoomNum2, fireType, fireInRoomNum2);
    dlist.AddController(fireContInWholeBuilding, fireType, fireInWholeBuilding);

    dlist.AddController(lightConRoomNum1, lightType, lightInRoomNum1);
    dlist.AddController(lightConRoomNum2, lightType, lightWholeFloor);

    //start
    SubcriberList lisrFireRoomNum1 = dlist.GetMailListByEvent(EventfireInRoomNum1);
    SubcriberList lisrFireRoomNum2 = dlist.GetMailListByEvent(EventfireInRoomNum2);
    SubcriberList lisrFireRoomNum3 = dlist.GetMailListByEvent(EventfireInRoomNum3);
    SubcriberList lisrLightRoomNum1 = dlist.GetMailListByEvent(EventLightInRoomNum1);
    SubcriberList lisrLightRoomNum2 = dlist.GetMailListByEvent(EventLightInRoomNum2);


    SendToList(lisrFireRoomNum1, EventfireInRoomNum1);
    SendToList(lisrFireRoomNum2, EventfireInRoomNum2);
    SendToList(lisrFireRoomNum3, EventfireInRoomNum3);

    SendToList(lisrLightRoomNum1, EventLightInRoomNum1);
    SendToList(lisrLightRoomNum2, EventLightInRoomNum2);

    //test
    ASSERT_EQUAL(fireConRoomNum1->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(fireConRoomNum2->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(fireContInWholeBuilding->GetNumOfEventsRecived() ,3);
    ASSERT_EQUAL(lightConRoomNum1->GetNumOfEventsRecived() ,1);
    ASSERT_EQUAL(lightConRoomNum2->GetNumOfEventsRecived() ,2);

END_UNIT


UNIT(controller_5_with_overlap_types) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type All("*");
    Type fireType("fire");
    Type lightType("light");
    Location allRoomNum1("1", "*");
    Location fireInRoomNum1("1", "1");
    Location fireInRoomNum2("2", "1");
    Location fireInRoomNum3("3", "1");
    Location fireInWholeBuilding("*", "*");
    Location lightInRoomNum1("1", "1");
    Location lightInRoomNum2("2", "1");
    Location lightWholeFloor("*", "1");

    SharedPtr<ControllerAgent> fireallRoomNum1 = MakeController(All, allRoomNum1, "14");
    SharedPtr<ControllerAgent> fireConAllRoomNum1 = MakeController(fireType, fireInRoomNum1, "3");
    SharedPtr<ControllerAgent> fireConRoomNum2 = MakeController(fireType, fireInRoomNum2, "2");
    SharedPtr<ControllerAgent> fireContInWholeBuilding = MakeController(fireType, fireInWholeBuilding, "3");
    
    SharedPtr<ControllerAgent> lightConRoomNum1 = MakeController(lightType, lightInRoomNum1, "5");
    SharedPtr<ControllerAgent> lightConRoomNum2 = MakeController(lightType, lightWholeFloor, "2");

    //events
    ID eventId("2");
    SharedPtr<Event> EventfireallRoomNum1(new Event(eventId, All, allRoomNum1));
    SharedPtr<Event> EventfireInRoomNum1(new Event(eventId, fireType, fireInRoomNum1));
    SharedPtr<Event> EventfireInRoomNum3(new Event(eventId, fireType, fireInRoomNum3));
    SharedPtr<Event> EventLightInRoomNum1(new Event(eventId, lightType, lightInRoomNum1));
    SharedPtr<Event> EventLightInRoomNum2(new Event(eventId, lightType, lightInRoomNum2));

    dlist.AddController(fireConAllRoomNum1, All, allRoomNum1);
    dlist.AddController(fireConRoomNum2, fireType, fireInRoomNum2);
    dlist.AddController(fireContInWholeBuilding, fireType, fireInWholeBuilding);

    dlist.AddController(lightConRoomNum1, lightType, lightInRoomNum1);
    dlist.AddController(lightConRoomNum2, lightType, lightWholeFloor);

    //start
    //SubcriberList lisrFireRoomNum1 = dlist.GetMailListByEvent(EventfireInRoomNum1);
    SubcriberList lisrFireRoomNum2 = dlist.GetMailListByEvent(EventfireInRoomNum1);
    SubcriberList lisrFireRoomNum3 = dlist.GetMailListByEvent(EventfireInRoomNum3);
    SubcriberList lisrLightRoomNum1 = dlist.GetMailListByEvent(EventLightInRoomNum1);
    SubcriberList lisrLightRoomNum2 = dlist.GetMailListByEvent(EventLightInRoomNum2);


    //SendToList(lisrFireRoomNum1, EventfireInRoomNum1);
    SendToList(lisrFireRoomNum2, EventfireInRoomNum1);
    SendToList(lisrFireRoomNum3, EventfireInRoomNum3);

    SendToList(lisrLightRoomNum1, EventLightInRoomNum1);
    SendToList(lisrLightRoomNum2, EventLightInRoomNum2);

    //test
    ASSERT_EQUAL(fireConAllRoomNum1->GetNumOfEventsRecived() , 2);
END_UNIT

UNIT(wild_card) 
    //initialize 
    DistributionList dlist;

    //controllers
    Type fireType("fire");
    Type lightType("light");
    Type All("*");

    Location wildCard("*", "*");

    Location fireInRoomNum1("1", "1");
    Location fireInRoomNum2("2", "1");
    Location fireInRoomNum3("3", "1");
    Location fireInWholeBuilding("*", "*");
    Location lightInRoomNum1("1", "1");
    Location lightInRoomNum2("2", "1");
    Location lightWholeFloor("*", "1");
    
    SharedPtr<ControllerAgent> wildController = MakeController(All, wildCard, "1");
    SharedPtr<ControllerAgent> wildControllerFire = MakeController(fireType, wildCard, "1");
    SharedPtr<ControllerAgent> wildControllerLights = MakeController(lightType, wildCard, "1");

    SharedPtr<ControllerAgent> fireConRoomNum1 = MakeController(fireType, fireInRoomNum1, "1");
    SharedPtr<ControllerAgent> fireConRoomNum2 = MakeController(fireType, fireInRoomNum2, "2");
    SharedPtr<ControllerAgent> fireContInWholeBuilding = MakeController(fireType, fireInWholeBuilding, "3");
    
    SharedPtr<ControllerAgent> lightConRoomNum1 = MakeController(lightType, lightInRoomNum1, "1");
    SharedPtr<ControllerAgent> lightConRoomNum2 = MakeController(lightType, lightWholeFloor, "2");

    //events
    ID eventId("1");
    SharedPtr<Event> EventfireInRoomNum1(new Event(eventId, fireType, fireInRoomNum1));
    SharedPtr<Event> EventfireInRoomNum2(new Event(eventId, fireType, fireInRoomNum2));
    SharedPtr<Event> EventfireInRoomNum3(new Event(eventId, fireType, fireInRoomNum3));
    SharedPtr<Event> EventLightInRoomNum1(new Event(eventId, lightType, lightInRoomNum1));
    SharedPtr<Event> EventLightInRoomNum2(new Event(eventId, lightType, lightInRoomNum2));

    dlist.AddController(wildController, All, wildCard);
    dlist.AddController(wildControllerFire, fireType, wildCard);
    dlist.AddController(wildControllerLights, lightType, wildCard);

    dlist.AddController(fireConRoomNum1, fireType, fireInRoomNum1);
    dlist.AddController(fireConRoomNum2, fireType, fireInRoomNum2);
    dlist.AddController(fireContInWholeBuilding, fireType, fireInWholeBuilding);

    dlist.AddController(lightConRoomNum1, lightType, lightInRoomNum1);
    dlist.AddController(lightConRoomNum2, lightType, lightWholeFloor);

    //start
    SubcriberList lisrFireRoomNum1 = dlist.GetMailListByEvent(EventfireInRoomNum1);
    SubcriberList lisrFireRoomNum2 = dlist.GetMailListByEvent(EventfireInRoomNum2);
    SubcriberList lisrFireRoomNum3 = dlist.GetMailListByEvent(EventfireInRoomNum3);
    SubcriberList lisrLightRoomNum1 = dlist.GetMailListByEvent(EventLightInRoomNum1);
    SubcriberList lisrLightRoomNum2 = dlist.GetMailListByEvent(EventLightInRoomNum2);

    SendToList(lisrFireRoomNum1, EventfireInRoomNum1);
    SendToList(lisrFireRoomNum2, EventfireInRoomNum2);
    SendToList(lisrFireRoomNum3, EventfireInRoomNum3);

    SendToList(lisrLightRoomNum1, EventLightInRoomNum1);
    SendToList(lisrLightRoomNum2, EventLightInRoomNum2);

    //test
    ASSERT_EQUAL(wildControllerFire->GetNumOfEventsRecived() , 3);
    ASSERT_EQUAL(wildControllerLights->GetNumOfEventsRecived() , 2);
    ASSERT_EQUAL(wildController->GetNumOfEventsRecived() , 5);


END_UNIT

TEST_SUITE(mvpTest) 
    TEST(controller_1) 
    TEST(controller_2) 
    TEST(controller_3) 

    TEST(controller_5_no_overlap) 
    TEST(controller_5_with_overlap)
    TEST(controller_5_with_overlap_types) 
    TEST(wild_card)  
END_SUITE 
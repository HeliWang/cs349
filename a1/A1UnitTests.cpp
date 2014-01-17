// A1 Unit Tests

#include "gtest/gtest.h"
#include "StopWatch.h"
#include "XApplication.h"

using namespace cs349;

/***
 * Edward Yang
 * This file contains 7 unit tests.
 * Default 1,2 are original tests provided with the assignment.
 * There should be a delay between most of the events.
 * ----
 * Test 1: EdwardTestStartStop, to test start/stop functionality (Line 106)
 * 
 * Random clicks, should not start.
 * Clicking start, should start.
 * Random clicks, should not stop.
 * Clicking stop, should stop.
 * ----
 * Test 2: EdwardTestReset, to test reset functionality (Line 193)
 *
 * Random clicks, should be reset.
 * Click start, should not be reset.
 * Random clicks, should not be reset.
 * Click stop, should not be reset.
 * Click reset, should be reset.
 * ----
 * Test 3: EdwardTestPause, to test pause functionality (Line 274)
 *
 * Random clicks, should not be paused.
 * Click start, should not be paused.
 * Random clicks, should not be paused.
 * Click stop, should be paused.
 * Click reset, should not be paused. (since reset)
 * ----
 * Test 4: EdwardTestLaps, to test lap functionality (Line 336)
 *
 * Click start, should be no laps.
 * Click lap, should be 1 lap.
 * Click lap, should be 2 laps.
 * Click lap, should be 3 laps.
 * Click pause, should be 3 laps.
 * Click reset, should be no laps.

 * ----
 * Test 5: EdwardTestShortFull, start/lap/pause/resume/pause/reset test. (Line 412)
 * ----
 * Test 6: EdwardTestLongFull, does multiple small clicks. (Line 507)
 *
 * does xxx
 * ----
 */

void EdwardPause(){
    /*XEvent event; // save the event here
    while( true ) {  // event loop until 'exit'
        XNextEvent( XApplication::GetInstance()->GetXDisplay(), &event ); // wait for next event
        if( event.type == KeyPress) break;
    }
    */
}
//default test #1
TEST(A1UnitTestDemos, Construction) {
  StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    
  EXPECT_FALSE(watch == NULL);
  EXPECT_FALSE(watch->IsRunning());

  EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
  EXPECT_FALSE(queue == NULL);
  queue->ClearEventQueue(); // Need to clear the event queue of any
                            // events our watch window has generated,
                            // or else subsequent processing of those
                            // events will fail miserably (i.e., core
                            // dump) if events from the event queue
                            // are processed after the watch pointer
                            // is deleted below.

  delete watch;
    
    
}

//default test #2
TEST(A1UnitTestDemos, Interaction) {
  StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
  EXPECT_FALSE(watch == NULL);

  // Create a synthetic mouse event to test whether watch responds to it
  // or not. Note that this assumes that clicking in the location
  // specified amounts to pressing the start/stop button. Your actual
  // interaction will likely be different, making this test useless.
  // However, this should provide a template for how to do unit tests
  // for interaction.
  EXPECT_FALSE(watch->GetParentWindow() == NULL);
  MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));

  EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
  EXPECT_FALSE(queue == NULL);

  EXPECT_FALSE(watch->IsRunning());
  queue->AddEventToQueue(e);
  unsigned int max_num_tries_to_flush_queue = 10;
  while (max_num_tries_to_flush_queue-- > 0
         && queue->GetNumEventsInQueue() > 0
         && !watch->IsRunning())
    {
      queue->ProcessNextEvent();
    }
  EXPECT_TRUE(watch->IsRunning());

  queue->ClearEventQueue();
  delete watch;

    
  // We do not need to delete the mouse event that we created, because
  // it will be deleted automatically by the EventQueue.
}

//Edward Yang Test #1 - Start/Stop
//This unit tests checks where or not start / stop button works!
TEST(A1UnitTestDemos,EdwardTestStartStop) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
//    watch->SetVisible(true);
//    watch->Paint(watch->GetGraphics());
//    watch->HandlePaintEvent(PaintEvent(watch,watch->GetBounds()));
//    XFlush(XApplication::GetInstance()->GetXDisplay());
    
    EXPECT_FALSE(watch == NULL);
    EXPECT_FALSE(watch->IsRunning());
    
    //ensure queue works
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    EXPECT_FALSE(queue == NULL);
    
    
    
    //random click, not on start button
    MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(190,231));
    queue->AddEventToQueue(e);
    unsigned int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    
//    usleep(500000);
    
    //click in empty space where reset/lap button is
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,231));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());

//    usleep(500000);
    
    //actually click on start
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    
    //let it run for a seconds
    
//    usleep(1000000);
    
    //click in empty state next to "stop" button
    //random click, not on start button
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(190,231));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    
//    sleep(500000);
    
    //actually click on stop
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(250,200));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());

    //sleep(200);
    
    
    
    //click reset - this has no effect on watch running :)
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    
    
    delete watch;
}

//Edward Yang Test #2 - Reset
TEST(A1UnitTestDemos,EdwardTestReset) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    EXPECT_FALSE(watch == NULL);
    EXPECT_FALSE(watch->IsRunning());
    
    //ensure queue works
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    EXPECT_FALSE(queue == NULL);
    
    //should be reset to start
    EXPECT_TRUE(watch->IsReset());
    
    //random click, not on start button, should still be reset
    MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(190,231));
    queue->AddEventToQueue(e);
    unsigned int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsReset());
    
    //sleep(500);
    
    //click in empty space where reset/lap button is, should have no effect
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,231));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsReset());
    
    //sleep(500);
    
    //actually click on start, no longer in reset state
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsReset());
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //actually click on stop, shouldnt have reset yet
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(250,200));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsReset());
    
    //sleep(1000);
    
    //click reset - this should reset everything
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsReset());
    
    delete watch;
}

//Edward Yang Test #3 - Pause
//New Start = !running,reset
//Paused = !running,!reset
//Running = running,!reset
TEST(A1UnitTestDemos,EdwardTestPause) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    EXPECT_FALSE(watch == NULL);
    EXPECT_FALSE(watch->IsRunning());
    
    //ensure queue works
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    EXPECT_FALSE(queue == NULL);
    
    //should be reset to start
    EXPECT_TRUE(watch->IsReset());
    
    //actually click on start. should NOT be pasued
    MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //click on stop, should be paused (!running,!reset) and not reset
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(250,200));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    
    //sleep(1000);
    
    //click reset - this should reset everything and NOT pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());

    
    delete watch;
}

//Edward Yang Test #4 - Laps
TEST(A1UnitTestDemos,EdwardTestLaps) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    //sleep(500);
    MouseEvent*e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //no laps yet
    EXPECT_TRUE(watch->NumOfLaps() == 0);

    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1200);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->NumOfLaps() == 2);
    
    //sleep(1323);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->NumOfLaps() == 3);

    //sleep(1000);
    
    //pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->NumOfLaps() == 3);
    
    //sleep(1000);
    
    //click reset - this should reset everything, so no laps.
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    delete watch;
}

//Edward Yang Test #5 - Short Full Test
TEST(A1UnitTestDemos,EdwardTestShortFull) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    //sleep(1000);
    
    MouseEvent*e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1000);
    
    //pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1000);
    
    //resume
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp,Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1000);
    
    //pause/stop
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1000);
    
    //click reset
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    delete watch;
}

//Edward Yang Test #6 - Long Full Test
TEST(A1UnitTestDemos,EdwardTestLongFull) {
    StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 390, 270));
    EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
    
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    int max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //resume
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp,Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //pause/stop
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //click reset
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    // --------------------------------------------------------------------------
    // RUNNING A SECOND IDENTICAL RUN
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //resume
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp,Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //pause/stop
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //click reset
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    // --------------------------------------------------------------------------
    // THROW IN A NEW ONE
    
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0
           && !watch->IsRunning())
    {
        queue->ProcessNextEvent();
    }
    
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    
    //let it run for 2 seconds
    //sleep(2000);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 1);
    
    //sleep(1234);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 2);
    
    //sleep(912);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 3);
    
    
    //pause
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 3);
    
    //resume
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp,Point(233,191));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 3);
    
    //sleep(1000);
    
    //click laps
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(342,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_TRUE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 4);

    //sleep(800);
    
    //pause/stop
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(232,220));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_FALSE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 4);
    
    //click reset
    e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(292,211));
    queue->AddEventToQueue(e);
    max_num_tries_to_flush_queue = 10;
    while (max_num_tries_to_flush_queue-- > 0
           && queue->GetNumEventsInQueue() > 0)
    {
        queue->ProcessNextEvent();
    }
    EXPECT_FALSE(watch->IsRunning());
    EXPECT_TRUE(watch->IsReset());
    EXPECT_TRUE(watch->NumOfLaps() == 0);
    delete watch;
}
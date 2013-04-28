// MMFApp.cpp: implementation of the MMFApp class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFApp.h"
#include "MMFBitmapLoader.h"
#include "MMFTGALoader.h"
#include "MMFXmlPage.h"
#include "MMFImage.h"
#include "MMFUsefullEnumerations.h"


/////////////////onstruction/Destruction
//////////////////////////////////////////////////////////////////////

MMFApp::MMFApp()
{
		  CoInitialize(NULL);
		m_bFirstTime = true;	
	
}

MMFApp::~MMFApp()
{
	list.SaveTofile("c:\\HelloWorld.txt");

	CoUninitialize();

}


int MMFApp::Run() //when this function exits the application exits
{
MSG		msg;									// Windows Message Structure
BOOL	done=FALSE;								// Bool Variable To Exit Loop

	
while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE

			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message

				//gets messages from queue and sends them to 
			//WindowProc which handles the processing of messages for all windows
			}
		}//if no messages then perform application processing 
			


		//application processing goes here 
		processAppLoop();

	}



return 0;

}


void MMFApp::processAppLoop(void){
	//char * m;

		if (m_bFirstTime){ //only show main app window first loop
		window.Register();
		window.Create("Hello world",800,600 ,16 , false);	
		window.Show();
		m_bFirstTime = false;
		//	window1.Register();
	//	window1.Create("hello");
	//	window1.Show();
	//	MMFImage image(MMF_WIN);
	//	image.LoadFromFile("bitmap8.BMP");
	//	image.Show(window1.getHWND());
		
		//MMFString stringHand;
		//LPCTSTR str = "C:\\ProggieFiles\\gorge.bmp";
		//LPTSTR Res = new TCHAR[_tcslen (str)];// allocate buffer 
		//stringHand.extractFileName(str,Res);
		//MessageBox(NULL, Res,NULL,1);

		//MMFImage image(MMF_OGL);
		//image.LoadFromFile("C:\\ProggieFiles\\gorge.tga");
	/*	list.add("hello");
		list.add("world");
		list.add("how");
		list.add("are");
		list.add("ya");*/
		
		//MMFXmlPage Page(MMF_OGL);
		//Page.loadXMLDoc("C:\\me.xml");
		//Page.LoadPage();
	
		}

		
	window.DrawGLScene();
	
	///	

}
void  MMFApp::addWindow(HWND hWnd){

/*	if (m_iwindowCount < MAXWINDOWS){
	m_iwindowCount++;


	}*/

}

/*void MMFApp::ShowaWindow(int index){

	if (index <  (m_iwindowCount -1)) {
	 MMFWindow * winObject = (*m_windows[index])->
	 winObject->Show();
	}

}
*/



int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State

{

MMFApp theApp;
theApp.Run(); // when the app exits we are done 
return 0;

}

bool isMMFOGLWindow(MMFWindow* windowObject){
	MMFOGLWindow * win = NULL;
	if(win = dynamic_cast<MMFOGLWindow *>(windowObject))
		return true;
	else 
		return false;
}
bool isMMFWindow(MMFWindow* windowObject){
	MMFWindow * win = NULL;
	if(win = dynamic_cast<MMFWindow *>(windowObject))
		return true;
	else 
		return false;

}
bool isMMFOGLWindowOrMMFWindow(MMFWindow* windowObject){
	if (isMMFOGLWindow(windowObject) || isMMFWindow(windowObject))
		return true;
	else
		return false;
}


LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wparam,LPARAM lparam)
{
	bool messageHandled = false;

	if (message ==WM_CREATE ){
		CREATESTRUCT * createstruct;
		createstruct = (CREATESTRUCT*) lparam;

		SetWindowLong(window,0, (LONG) (createstruct->lpCreateParams));

		messageHandled  = true;
	}



	if (message == WM_SYSCOMMAND)							// Intercept System Commands
		{
			switch (wparam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
										// Exit
		}
	
	 MMFWindow * object = (MMFWindow*) GetWindowLong(window,0);
    
/*
	if (strcmp( (LPTSTR)typeid( *temp ).name(), (LPTSTR) "class MMFOGLWindow" ) ==0){
	 MMFOGLWindow * object = dynamic_cast<MMFOGLWindow*>(temp);
 	
	}*/

	//CRETAE SOME LOGIC HERE TO DETERMINE OBJECT TYPE 
	if (isMMFOGLWindowOrMMFWindow(object)) {
		MMFWindow* ThisWindow = NULL;

		if (isMMFOGLWindow(object) )
			ThisWindow = (MMFOGLWindow*) GetWindowLong(window,0);
		else 
			ThisWindow = (MMFWindow*) GetWindowLong(window,0);

		switch (message){
	//	case WM_DESTROY: 
		//	{
		//	ThisWindow->Destroy(window,message, wparam, lparam);
		//	break;
		//	}
	case WM_CLOSE: 
	{			 	
				 object->Destroy(window,message, wparam, lparam);
				 messageHandled  = true;
		 
		}
	break;
		case WM_SIZE:
			{
			ThisWindow->Resize(LOWORD(lparam), HIWORD(lparam)); //Loword = width, hiword = height
			messageHandled  = true;
			
			}
		break;
		default:
			{
			messageHandled = ThisWindow->HandleMessage(message,wparam,lparam);//let the window handle its own messages
			
			}
			break;
		}

	}

			
	if (!messageHandled) 
		return DefWindowProc(window, message,wparam,lparam);
	else
		return 0;
}


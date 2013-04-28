// MMFOGLWindow.cpp: implementation of the MMFOGLWindow class.
//
//////////////////////////////////////////////////////////////////////
#include "MMFTGALoader.h"
#include "MMFOGLWindow.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Texture g_texture;
MMFTGALoader g_tgaLoader;
unsigned int  g_textureStorage[1];

const float piover180 = 0.0174532925f;
int drawQuads();
int LoadGLTextures();
GLfloat gLightPosition[]= { 0.0f, 10.0f, 500.0f, 1.0f };


MMFOGLWindow::MMFOGLWindow()
{
	m_camera.x = 0.0f;
	m_camera.y = 10.0f;
	m_camera.z = 500.0f;
	m_camera.yrot = 0.0f;

	m_bFullscreen = false;

}

MMFOGLWindow::~MMFOGLWindow()
{

}
void showLastErrortoScreen(void){

LPVOID lpMsgBuf;


FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    GetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL );
    
MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
    
LocalFree( lpMsgBuf );


}
void MMFOGLWindow::doLogic(void){

	if (m_keys[VK_RIGHT]) 
		m_camera.yrot -= 1.5f;

	if (m_keys[VK_LEFT]) 
		m_camera.yrot += 1.5f;

	if (m_keys[VK_UP])
	{
		m_camera.x -= (float)sin(m_camera.yrot*piover180) * 5.0f; // Move On The X-Plane Based On Player Direction
		m_camera.z -= (float)cos(m_camera.yrot*piover180) * 5.0f; // Move On The Z-Plane Based On Player Direction
	}

	if (m_keys[VK_DOWN]) {
		m_camera.x += (float)sin(m_camera.yrot*piover180) * 5.0f; // Move On The X-Plane Based On Player Direction
		m_camera.z += (float)cos(m_camera.yrot*piover180) * 5.0f; // Move On The Z-Plane Based On Player Direction
	}
		
	//gLightPosition[0] = m_camera.x;
//	gLightPosition[1] = m_camera.x;

}

drawFloor(){
glBegin(GL_QUADS);
glTexCoord2f(0, 0);
glVertex3f(-500,0.01f,500);  
 
glTexCoord2f(1, 0);
glVertex3f(500,0.01f,500); 


glTexCoord2f(1, 1);
glVertex3f(500,0.01f,-500);  

glTexCoord2f(0, 1);
glVertex3f(-500,0.01f,-500);

glEnd();
}

int MMFOGLWindow::DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	doLogic();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
glLightfv(GL_LIGHT1, GL_POSITION,gLightPosition);		
		
	glRotatef(360 - m_camera.yrot,0, 1.0f,0);

drawSky();	
		
		
		glTranslatef(-m_camera.x,-m_camera.y,-m_camera.z);// Reset The Current Modelview Matrix
		
drawFloor();


	//glPointSize(10);
//	glColor3b(255,255,255);
	//glBegin(GL_POINTS);
//	glVertex3d(0,0,1);
//	glEnd();
	
	loader.RenderObject(0); 


//	drawQuads();
	SwapBuffers(m_hDC);
	return TRUE;										// Everything Went OK
}

void MMFOGLWindow::drawSky(void){

glBindTexture(GL_TEXTURE_2D, m_skyTex->m_uiTexID);

//sky
glEnable(GL_TEXTURE_2D); 

glBegin(GL_QUADS);
glTexCoord2f(0, 0);
glVertex3f(-500,100,500);  
 
glTexCoord2f(1, 0);
glVertex3f(500,100,500); 


glTexCoord2f(1, 1);
glVertex3f(500,100,-500);  

glTexCoord2f(0, 1);
glVertex3f(-500,100,-500);

glEnd();



//floor
//glBindTexture(GL_TEXTURE_2D, m_skyTex->m_uiTexID);
/*glBegin(GL_QUADS);
glTexCoord2f(0, 0);
glVertex3f(-500,0.0f,-500);
  
 
glTexCoord2f(1, 0);
glVertex3f(500,0.0f,-500); 
 


glTexCoord2f(1, 1);
glVertex3f(500,0.0f,500);

glTexCoord2f(0, 1);
glVertex3f(-500,0.0f,500);

glEnd();*/
glDisable(GL_TEXTURE_2D);	

}
bool MMFOGLWindow::Register(void){

	



	WNDCLASS	wc;						// Windows Class Structure


	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		=  WindowProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 4;								// No Extra Window Data
	wc.hInstance		= Manager.GetInstance();							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

		if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
return true;
}

bool MMFOGLWindow::Create(char* title,int width, int height, int bits, bool fullscreenflag){
	
	MMF3DObject obj;
	loader.LoadFile("C:\\portfolio\\library\\MMFramework\\MultimediaFrameWorkV1_b\\city.3DS");
	m_iWidth = width;
	m_iHeight = height;

	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)m_iWidth;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)m_iHeight;		// Set Bottom Value To Requested Height

	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	
	m_bFullscreen =fullscreenflag;			// Set The memberFullscreen Flag


	if (m_bFullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= m_iWidth;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= m_iHeight;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_bFullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (m_bFullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
	LPVOID params = this;
	// Create The Window
	if (!(m_hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								Manager.GetInstance(),							// Instance
								params)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(m_hDC=GetDC(m_hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
	
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(m_hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
	KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(m_hRC=wglCreateContext(m_hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(m_hDC,m_hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	
	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Displa
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
return 0;

}

MMFOGLWindow::Show(){
ShowWindow(m_hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(m_hWnd);						// Slightly Higher Priority
	SetFocus(m_hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(m_iWidth, m_iHeight);					// Set Up Our Perspective GL Screen
}


GLvoid MMFOGLWindow::KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (m_bFullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (m_hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC))						// Are We Able To Delete The RC?
		{
			showLastErrortoScreen();
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL;										// Set RC To NULL
	}

	if (m_hDC && !ReleaseDC(m_hWnd,m_hDC))					// Are We Able To Release The DC
	{
		showLastErrortoScreen();
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;										// Set DC To NULL
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))					// Are We Able To Destroy The Window?
	{
		showLastErrortoScreen();
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",Manager.GetInstance()))			// Are We Able To Unregister Class
	{
		showLastErrortoScreen();
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
									// Set hInstance To NULL
	}
}


int MMFOGLWindow::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{


//LoadGLTextures();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

		m_skyTex = new Texture;
	m_tgaLoader.LoadTGA(m_skyTex, "C:\\portfolio\\library\\MMFramework\\MultimediaFrameWorkV1_b\\image\\sky.TGA");
//	m_tgaLoader.LoadTGA(m_skyTex, "C:\\portfolio\\library\\MMFramework\\MultimediaFrameWorkV1_b\\Compressed.TGA");
	glGenTextures(1, &m_skyTex->m_uiTexID);
	glBindTexture(GL_TEXTURE_2D, m_skyTex->m_uiTexID); // Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtered
	glTexImage2D(GL_TEXTURE_2D, 0, m_skyTex->muiType, m_skyTex->m_uiWidth, m_skyTex->m_uiHeight, 0, m_skyTex->muiType,
	GL_UNSIGNED_BYTE, m_skyTex->m_ucImageData);

	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightDiffuse[]= { 0.2f, 0.2f, 0.2f, 1.0f }; //

//GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f }; // Light Position ( NEW )
glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);

   GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0f };
    GLfloat mat_shininess[] = { 128};
 

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT1);
	//} 
	//else MessageBox(NULL, "Failed ","hi", 1);
	return TRUE;										// Initialization Went OK
}


GLvoid MMFOGLWindow::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.01f,1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{

char * filename = "targ.TGA";
if (!g_tgaLoader.LoadTGA(&g_texture, filename))
{
	exit(0);
}
glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending (disable alpha testing)	glEnable(GL_BLEND);							// Enable Blending       (disable alpha testing)
//	glAlphaFunc(GL_GREATER,0.1f);						// Set Alpha Testing     (disable blending)
//	glEnable(GL_ALPHA_TEST);						// Enable Alpha Testing  (disable blending)

//glBlendFunc(GL_SRC_ALPHA,GL_ONE);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )

//g_textureStorage = new unsigned int[g_texture.m_uiWidth * g_texture.m_uiHeight];
		glGenTextures(1, &g_textureStorage[0]);					// Create The Texture
if (g_texture.muiType == GL_RGBA)
MessageBox(NULL,"GL_RGBA",NULL,MB_OK | MB_ICONINFORMATION);
	
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, g_textureStorage[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, g_texture.muiType, g_texture.m_uiWidth, g_texture.m_uiHeight, 0,g_texture.muiType, GL_UNSIGNED_BYTE, g_texture.m_ucImageData);
	//	glTexImage2D(GL_TEXTURE_2D, 0, g_texture.m_uiBpp / 8, g_texture.m_uiWidth, g_texture.m_uiHeight, 0,g_texture.muiType, GL_UNSIGNED_BYTE, g_texture.m_ucImageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	


	return true;									// Return The Status
}



int drawQuads(){

	glBindTexture(GL_TEXTURE_2D,  *g_textureStorage);

		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();

	return 1;

}


bool MMFOGLWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam){
bool messageHandled = false;
switch (msg) {
	case WM_SYSCOMMAND://intercept powersave/screensaver
	{ 
		switch(wParam) 
		{
		case SC_SCREENSAVE: 
		case SC_MONITORPOWER:
		messageHandled = true;
		}
		break;
	}
	case WM_KEYDOWN:	
		{
		KeyDown(wParam);
		messageHandled = true;
		}
		break;
	case WM_KEYUP: 
		{
		KeyUp(wParam);
		messageHandled = true;
		}
		break;
}





return messageHandled;

}


LRESULT MMFOGLWindow::Destroy(HWND, UINT, WPARAM,LPARAM){
	KillGLWindow();
    PostQuitMessage(0);
	return 0;

}

void MMFOGLWindow::Resize(int width, int height){
	ReSizeGLScene(width, height);
}
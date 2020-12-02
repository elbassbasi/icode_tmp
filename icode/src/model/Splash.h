/*
 * Splash.h
 *
 *  Created on: 22 déc. 2019
 *      Author: azeddine
 */

#ifndef SRC_ICODE_UI_SPLASH_H_
#define SRC_ICODE_UI_SPLASH_H_
#include "../icode.h"
class Splash: public WShell,
		public IWRunnable,
		public IProgressMonitor,
		public IProgressMonitorTask {
public:
	WThread backgroundThread;
	//WImage image;
	WFont font;
	WProgressBar progress;
	//WLabel label;
	bool update_finish :1;
	bool update_text :1;
	bool update_progress :1;
	bool update_progress_max :1;
	int progress_i;
	int progress_max;
	char text[0x100];
public:
	Splash();
	~Splash();
	void Create();
	void LoadPlugins();
protected:
	bool OnPaint(WPaintEvent &e);
	void OnUpdate();
	void _Update();
	bool OnTimer(WTimerEvent &e);
	void Run();
public:
	//IProgressMonitorTask
	void Close();
	int GetTotal();
	WString GetText();
	bool IsCanceled();
	void SetCanceled(bool value);
	void SetTotal(int total);
	void SetText(const char *format,...);
	void Worked(int work);
public:
	//IProgressMonitor
	IProgressMonitorTask* CreateTask(IProgressMonitorTask *parentTask);
	bool IsCanceledAll();
	void SetCanceledAll(bool value);
};

#endif /* SRC_ICODE_UI_SPLASH_H_ */

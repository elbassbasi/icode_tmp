/*
 * Splash.cpp
 *
 *  Created on: 22 déc. 2019
 *      Author: azeddine
 */

#include "Splash.h"
#include "../core/Managers.h"
Splash::Splash() {
	this->progress_max = 0;
	this->progress_i = 0;
	this->update_finish = false;
	this->update_text = false;
	this->update_progress = false;
	this->update_progress_max = false;
}

Splash::~Splash() {
}

void Splash::Create() {
	WShell::Create(W_NO_TRIM | W_FREE_MEMORY);
	WSize size(450, 250);
	WRect rect, r;
	WFont *font = this->GetFont();
	WFontData data;
	font->GetFontData(data);
	data.SetHeight(30);
	this->font.Create(data);
	progress.Create(this, 0);
	//label.Create(this, W_CENTER);
	WToolkit::GetDefault()->GetBounds(r);
	size.height += 50;
	this->SetBounds((r.width - size.width) / 2, (r.height - size.height) / 2,
			size.width, size.height);
	//this->ComputeTrim(rect, 0, 0, size.width, size.height);
	//this->SetBounds(100, 100, rect.width, rect.height);
	this->GetClientArea(rect);
	progress.SetBounds(0, rect.height - 25, rect.width, 20);
	//label.SetBounds(0, rect.height - 50, rect.width, 20);
	backgroundThread.Create(this);
	this->Open();
	SetTimer(500);
}

bool Splash::OnPaint(WPaintEvent &e) {
	WRect r;
	GetClientArea(r);
	e->SetBackground(W_COLOR_BLACK);
	e->FillRectangle(r);
	e->SetForeground(W_COLOR_WHITE);
	//e->SetFont(&this->font1);
	e->SetFont(WToolkit::GetDefault()->GetSystemFont());
	e->DrawTextTransparent(this->text, r.x, r.height - 50);
	e->SetFont(&this->font);
	e->SetForeground(W_COLOR_BLUE);
	e->DrawTextTransparent("ICode Editor", (r.x + r.width) / 2,
			(r.y + r.height) / 2);
	e->SetForeground(W_COLOR_WHITE);
	e->SetFont(WToolkit::GetDefault()->GetSystemFont());
	e->DrawTextTransparent("Intelligent code editor", (r.x + r.width) / 2,
			(r.y + r.height) / 2 + 50);
	return true;
}

void Splash::LoadPlugins() {
	Managers *managers = (Managers*) IManagers::Get();
	managers->LoadPlugins(0);
	this->progress_max = 20;
	this->update_progress_max = true;
	this->_Update();
	for (int i = 0; i < this->progress_max; i++) {
		WThread::Sleep(1);
		this->progress_i = i;
		this->update_progress = true;
		SetText("Loading Plugin %d", i);
	}
	this->update_finish = true;
	this->_Update();
}

void Splash::OnUpdate() {
	bool finish = true;
	if (this->update_text) {
		//label.SetText(this->text);
		this->update_text = false;
		finish = false;
		this->Redraw();
	}
	if (this->update_progress_max) {
		progress.SetMaximum(this->progress_max);
		this->update_progress_max = false;
		finish = false;
	}
	if (this->update_progress) {
		progress.SetSelection(this->progress_i);
		this->update_progress = false;
		finish = false;
	}
	if (this->update_finish && finish == true) {
		Managers *managers = (Managers*) IManagers::Get();
		managers->AttachPlugins(0);
		managers->StartPlugins(0);
		KillTimer();
		this->Dispose();
	}
}

bool Splash::OnTimer(WTimerEvent &e) {
	OnUpdate();
	return true;
}

void Splash::_Update() {
	//AsyncExec();
}

void Splash::Run() {
	LoadPlugins();
}
//IProgressMonitorTask
void Splash::Close() {
}

int Splash::GetTotal() {
	return progress.GetMaximum();
}

WString Splash::GetText() {
	return this->text;
}

bool Splash::IsCanceled() {
	return false;
}

void Splash::SetCanceled(bool value) {
}

void Splash::SetTotal(int total) {
	progress.SetMaximum(total);
}

void Splash::SetText(const char *format,...) {
	va_list args;
	va_start(args, format);
	vsnprintf(this->text, sizeof(this->text), format, args);
	va_end(args);
	this->update_text = true;
	this->_Update();
}

void Splash::Worked(int work) {
	progress.SetSelection(work);
}
//IProgressMonitor
IProgressMonitorTask* Splash::CreateTask(IProgressMonitorTask *parentTask) {
	return this;
}

bool Splash::IsCanceledAll() {
	return false;
}

void Splash::SetCanceledAll(bool value) {
}

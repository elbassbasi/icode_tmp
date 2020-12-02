/*
 * IProgressMonitor.h
 *
 *  Created on: 15 mai 2020
 *      Author: Azeddine El Bassbasi
 */

#ifndef ICODE_INCLUDE_RUNTIME_IPROGRESSMONITOR_H_
#define ICODE_INCLUDE_RUNTIME_IPROGRESSMONITOR_H_
#include "../core/core.h"
class IProgressMonitorTask: public IObject {
public:
	IID_CLASS(IProgressMonitorTask,0,1,1)
	virtual void Close()=0;
	virtual int GetTotal()=0;
	virtual WString GetText()=0;
	/**
	 * Returns whether cancelation of current operation has been requested.
	 * Long-running operations should poll to see if cancelation
	 * has been requested.
	 *
	 * @return <code>true</code> if cancellation has been requested,
	 *    and <code>false</code> otherwise
	 * @see #setCanceled(boolean)
	 */
	virtual bool IsCanceled()=0;
	/**
	 * Sets the cancel state to the given value.
	 *
	 * @param value <code>true</code> indicates that cancelation has
	 *     been requested (but not necessarily acknowledged);
	 *     <code>false</code> clears this flag
	 * @see #isCanceled()
	 */
	virtual void SetCanceled(bool value)=0;
	virtual void SetTotal(int total)=0;
	virtual void SetText(const char *format,...)=0;
	/**
	 * Notifies that a given number of work unit of the main task
	 * has been completed. Note that this amount represents an
	 * installment, as opposed to a cumulative amount of work done
	 * to date.
	 *
	 * @param work a non-negative number of work units just completed
	 */
	virtual void Worked(int work)=0;
};
class IStatus;
class IProgressMonitor: public IObject {
public:
	IID_CLASS(IProgressMonitor,0,1,1)

	/**
	 * Notifies that the main task is beginning.  This must only be called once
	 * on a given progress monitor instance.
	 *
	 * @param name the name (or description) of the main task
	 *  the main task is been subdivided. If the value is <code>UNKNOWN</code>
	 *  the implementation is free to indicate progress in a way which
	 *  doesn't require the total number of work units in advance.
	 */
	virtual IProgressMonitorTask* CreateTask(IProgressMonitorTask *parentTask)=0;

	/**
	 * Returns whether cancelation of current operation has been requested.
	 * Long-running operations should poll to see if cancelation
	 * has been requested.
	 *
	 * @return <code>true</code> if cancellation has been requested,
	 *    and <code>false</code> otherwise
	 * @see #setCanceled(boolean)
	 */
	virtual bool IsCanceledAll()=0;

	/**
	 * Sets the cancel state to the given value.
	 *
	 * @param value <code>true</code> indicates that cancelation has
	 *     been requested (but not necessarily acknowledged);
	 *     <code>false</code> clears this flag
	 * @see #isCanceled()
	 */
	virtual void SetCanceledAll(bool value)=0;
};

#endif /* ICODE_INCLUDE_RUNTIME_IPROGRESSMONITOR_H_ */

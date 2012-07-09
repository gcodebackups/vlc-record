/*------------------------------ Information ---------------------------*//**
 *
 *  $HeadURL$
 *
 *  @file     qhelpdialog.cpp
 *
 *  @author   Jo2003
 *
 *  @date     06.07.2012
 *
 *  $Id$
 *
 *///------------------------- (c) 2012 by Jo2003  --------------------------

#include "qhelpdialog.h"
#include "ui_qhelpdialog.h"

//---------------------------------------------------------------------------
//
//! \brief   constructs QHelpDialog object
//
//! \author  Jo2003
//! \date    06.07.2012
//
//! \param   parent pointer to parent widget
//! \param   helpFile string of help file name
//
//---------------------------------------------------------------------------
QHelpDialog::QHelpDialog (QWidget *parent, const QString &helpFile)
   : QDialog(parent),
     ui(new Ui::QHelpDialog), pHe(NULL)
{
   ui->setupUi(this);

   if (helpFile != "")
   {
      setHelpFile(helpFile);
   }
}

//---------------------------------------------------------------------------
//
//! \brief   destroys QHelpDialog object
//
//! \author  Jo2003
//! \date    06.07.2012
//
//---------------------------------------------------------------------------
QHelpDialog::~QHelpDialog()
{
   delete ui;
}

//---------------------------------------------------------------------------
//
//! \brief   dialog should be shown
//
//! \author  Jo2003
//! \date    09.07.2012
//
//! \param   event pointer to show event
//
//! \return  --
//---------------------------------------------------------------------------
void QHelpDialog::showEvent(QShowEvent *event)
{
   event->accept();
   QTimer::singleShot(10, this, SLOT(adjustSplitter()));
}

//---------------------------------------------------------------------------
//
//! \brief   adjust splitter sizes
//
//! \author  Jo2003
//! \date    09.07.2012
//
//! \return  --
//---------------------------------------------------------------------------
void QHelpDialog::adjustSplitter()
{
   int         i, j;
   QList<int> sz = ui->splitter->sizes();

   // adjust splitter to have good dimension ...
   // 1/5 <--> 4/5
   i = sz.value(0) + sz.value(1);
   j = (int)(i / 5);
   sz.clear();
   sz.insert(0, j);
   sz.insert(1, i - j);
   ui->splitter->setSizes(sz);
}

//---------------------------------------------------------------------------
//
//! \brief   set help file / display help
//
//! \author  Jo2003
//! \date    06.07.2012
//
//! \param   helpFile string of help file name
//! \param   parent pointer to parent widget
//
//! \return  --
//---------------------------------------------------------------------------
void QHelpDialog::setHelpFile(const QString &helpFile)
{
   if (pHe && (sFile != helpFile))
   {
      disconnect(ui->helpBrowser, SLOT(setSource(const QUrl &)));
      ui->helpBrowser->setHelpEngine(NULL);
      ui->splitter->widget(0)->deleteLater();

      delete pHe;
      pHe = NULL;
   }

   if (!pHe)
   {
      pHe = new QHelpEngine (helpFile, this);
      pHe->setupData();

      ui->helpBrowser->setHelpEngine(pHe);
      ui->splitter->insertWidget(0, pHe->contentWidget());
      connect(pHe->contentWidget(), SIGNAL(linkActivated(const QUrl &)),ui->helpBrowser, SLOT(setSource(const QUrl &)));
   }

   sFile = helpFile;
}

///////////////////////////////////////////////////////////////////////////////
// QHelpBrowser
///////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
//
//! \brief   constructs QHelpBrowser object
//
//! \author  Jo2003
//! \date    09.07.2012
//
//! \param   parent pointer to parent widget
//! \param   helpEngine pointer to QHelpEngine instance
//
//---------------------------------------------------------------------------
QHelpBrowser::QHelpBrowser(QWidget *parent, QHelpEngine *helpEngine)
   : QTextBrowser(parent), pHe(helpEngine)
{
   // nothing to do so far ...
}

//---------------------------------------------------------------------------
//
//! \brief   destroys QHelpBrowser object
//
//! \author  Jo2003
//! \date    09.07.2012
//
//---------------------------------------------------------------------------
QHelpBrowser::~QHelpBrowser()
{
   // nothing to do so far ...
}

//---------------------------------------------------------------------------
//
//! \brief   load resource either from QtHelp file or from resource system
//
//! \author  Jo2003
//! \date    09.07.2012
//
//! \param   type type of resource
//! \param   url file or url in QtHelp
//
//! \return  resource as QVariant (usually QByteArray)
//---------------------------------------------------------------------------
QVariant QHelpBrowser::loadResource(int type, const QUrl &url)
{
   if (pHe)
   {
      if (url.scheme() == "qthelp")
      {
         return QVariant(pHe->fileData(url));
      }
      else
      {
         return QTextBrowser::loadResource(type, url);
      }
   }

   return QVariant();
}

//---------------------------------------------------------------------------
//
//! \brief   set helpengine pointer
//
//! \author  Jo2003
//! \date    09.07.2012
//
//! \param   helpEngine Pointer to QHelpEngine
//
//! \return  --
//---------------------------------------------------------------------------
void QHelpBrowser::setHelpEngine(QHelpEngine *helpEngine)
{
   pHe = helpEngine;
}

/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.
 
 
 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

// Qt Gui Includes
#include <QtUtils/Bridge/QtBridge.h>

// Interface Includes
#include <Interface/ToolInterface/MeasurementToolInterface.h>
#include <Interface/ToolInterface/detail/MeasurementTableModel.h>
#include <Interface/ToolInterface/detail/MeasurementTableView.h>
#include "ui_MeasurementToolInterface.h"

// Application Includes
#include <Application/Tools/MeasurementTool.h>
#include <Application/Tools/detail/Measurement.h>

SCI_REGISTER_TOOLINTERFACE( Seg3D, MeasurementToolInterface )

namespace Seg3D
{

class MeasurementToolInterfacePrivate 
{
public:
	Ui::MeasurementToolInterface ui_;

	MeasurementTableModel*	table_model_;
	MeasurementTableView*	table_view_;
};

// constructor
MeasurementToolInterface::MeasurementToolInterface() :
	private_( new MeasurementToolInterfacePrivate )
{
}

// destructor
MeasurementToolInterface::~MeasurementToolInterface()
{
}

// build the interface and connect it to the state manager
bool MeasurementToolInterface::build_widget( QFrame* frame )
{
	//Step 1 - build the Qt GUI Widget
	this->private_->ui_.setupUi( frame );

	//Step 2 - get a pointer to the tool
	ToolHandle base_tool_ = tool();
	MeasurementTool* tool = dynamic_cast< MeasurementTool* > ( base_tool_.get() );
	
	// Get convenience pointers to measurement table view and model
	this->private_->table_view_ = this->private_->ui_.table_view_;
	this->private_->table_model_ = 
		qobject_cast< MeasurementTableModel* >( this->private_->table_view_->model() );

	//Step 3 - connect the gui to the tool through the QtBridge
	QtUtils::QtBridge::Connect( this->private_->ui_.copy_button_, boost::bind(
		&MeasurementTableView::copy, this->private_->table_view_ ) );

	// Connect note column and text box using Qt signals/slots since currently can't hook up two
	// widgets to same state object.
	QObject::connect( this->private_->table_model_, SIGNAL( active_note_changed( QString ) ), 
		this, SLOT( set_measurement_note_box( QString ) ) );
	QObject::connect( this->private_->ui_.note_textbox_, SIGNAL( textChanged() ), 
		this, SLOT( update_measurement_note_model() ) );

	//Send a message to the log that we have finished with building the Measure Tool Interface
	CORE_LOG_MESSAGE( "Finished building an Measure Tool Interface" );

	// Test code
	MeasurementList::Instance()->clear();

	this->private_->table_model_->update();

	return ( true );
} // end build_widget	

void MeasurementToolInterface::set_measurement_note_box( const QString & note )
{
	// If text edit has focus, this is a circular update from the model -- don't modify text
	if( !this->private_->ui_.note_textbox_->hasFocus() )
	{
		this->private_->ui_.note_textbox_->blockSignals( true );
		this->private_->ui_.note_textbox_->setText( note );
		this->private_->ui_.note_textbox_->blockSignals( false );
	}	
}

void MeasurementToolInterface::update_measurement_note_model()
{
	this->private_->table_model_->set_active_note( 
		this->private_->ui_.note_textbox_->document()->toPlainText() );
}

} // end namespace Seg3D
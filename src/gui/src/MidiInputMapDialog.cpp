#include <memory>

#include "MidiInputMapDialog.h"
#include "Skin.h"

#include <hydrogen/hydrogen.h>
using namespace H2Core;


MidiInputMapDialog::MidiInputMapDialog(QWidget *parent)
    : QDialog( parent )
    , Object( "MidiInputMapDialog" )
{
            setupUi( this );

            setWindowTitle( trUtf8( "Midi input map editor" ) );
            setWindowIcon( QPixmap( Skin::getImagePath()  + "/icon16.png" ) );

            midiTable->setRole( H2_MIDI_EVENT_MAP );
            midiTable->setupMidiTable();

            setMinimumSize( width(), height() );
            setMaximumSize( width(), height() );

            helpLabel->setText("This editor enables you to define the midi note on which each instrument responds.");
}

void MidiInputMapDialog::on_loadButton_clicked()
{
    static QString lastUsedDir = QDir::homePath();
    QString filename;

    std::auto_ptr<QFileDialog> fd( new QFileDialog );
    fd->setFileMode( QFileDialog::AnyFile );



    fd->setNameFilter( "Hydrogen midi event mapping (*.h2midimap)" );

    fd->setDirectory( lastUsedDir );
    fd->setAcceptMode( QFileDialog::AcceptOpen );
    fd->setWindowTitle( trUtf8( "Open midi event mapping" ) );


    if (fd->exec()) {
            filename = fd->selectedFiles().first();
    }

    if ( ! filename.isEmpty() ) {
          midiTable->loadFromFile( filename );
          currentFilename = filename;
    }
}

void MidiInputMapDialog::on_saveButton_clicked()
{
    if( currentFilename.isEmpty() ) on_saveAsButton_clicked();
    midiTable->saveToFile( currentFilename );
}

void MidiInputMapDialog::on_saveAsButton_clicked()
{
    static QString lastUsedDir = QDir::homePath();
    QString filename;

    std::auto_ptr<QFileDialog> fd( new QFileDialog );
    fd->setFileMode( QFileDialog::AnyFile );



    fd->setNameFilter( "Hydrogen midi event mapping (*.h2midimap)" );

    fd->setDirectory( lastUsedDir );
    fd->setAcceptMode( QFileDialog::AcceptSave );
    fd->setWindowTitle( trUtf8( "Save midi event mapping" ) );


    if (fd->exec()) {
            filename = fd->selectedFiles().first();
    }

    if ( ! filename.isEmpty() ) {
          midiTable->saveToFile( filename );
          currentFilename = filename;
    }
}

void MidiInputMapDialog::on_defaultButton_clicked()
{

}



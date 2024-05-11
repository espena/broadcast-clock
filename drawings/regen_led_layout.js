/**********************************************************************************************************************
* QCAD Script for annotating and exporting LED layout to KiCAD footprint file                                         *
* Espen Andersen, www.espenandersen.no                                                                                *
* IMPORTANT: Put center of clock dial at grid datum (0.000;0.000) before running script                               *
***********************************************************************************************************************/

// Upper left point, offset in mm from KiCADs default origin (0,0)
var KICAD_OFFSET_MM_FROM_ORIGIN = {
  x: 25.6540,
  y: 25.6540
};

var DESIGNATOR_PREFIX = 'D'; // < Component reference

// Prepare QCAD objects
var di = EAction.getDocumentInterface();
var doc = EAction.getDocument();
var docCenter = doc.getBoundingBox().getCenter();
var objects = doc.queryAllEntities();

// Clock face, sections
var ledsMatrix = [ ];
var ledsSeparators = [ ];
var ledsDialSeconds = [ ];
var ledsDialHours = [ ];

// QCAD layer IDs
var dialSecondsLayer   = doc.getLayerId( '0 ... dial_seconds' );
var dialHoursLayer     = doc.getLayerId( '0 ... dial_hours' );
var dialSeparatorLayer = doc.getLayerId( '0 ... dial_separator' );
var dotMatrixLayer     = doc.getLayerId( '0 ... display_matrices' );
var designatorsLayer   = doc.getLayerId( '0 ... designators' );

// Items to be deleted (text entities from previous run)
var opDel = new RDeleteObjectsOperation();

// Templatized KiCAD footprint of a standard LED
function getKiCADFootprintSection( x, y, designator, diameter ) {
  return (
    '(footprint "LED_THT_espena:LED_D' + diameter + '.0mm" (layer "F.Cu")\n' +
    '  (tstamp 13558179-6df8-4315-aa3c-2ffd57492aea)\n' +
    '  (at ' + x + ' ' + y + ')\n' +
    '  (descr "LED, diameter ' + diameter + '.0mm, 2 pins")\n' +
    '  (tags "LED diameter ' + diameter + '.0mm 2 pins")\n' +
    '  (attr through_hole)\n' +
    '  (fp_text reference "' + designator + '" (at 0 -2.96) (layer "F.SilkS")\n' +
    '      (effects (font (size 1 1) (thickness 0.15)))\n' +
    '    (tstamp 3bf72d73-f4e8-49ca-b147-8dbcf3b495a3)\n' +
    '  )\n' +
    '  (fp_line (start -1.56 -1.236) (end -1.56 -1.08)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp 0512896f-b541-4561-9f57-b8efe24d9133))\n' +
    '  (fp_line (start -1.56 1.08) (end -1.56 1.236)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp c89043ae-ee4a-49c6-a32a-30532dd23476))\n' +
    '  (fp_arc (start -1.56 -1.235516) (mid 0.096487 -1.987659) (end 1.672335 -1.078608)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp 633b40fa-c491-45c2-9bca-d26c9a2e7f92))\n' +
    '  (fp_arc (start -1.040961 -1.08) (mid 0.000117 -1.5) (end 1.04113 -1.079837)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp 607dcc7d-543f-4fbc-a4e5-468f8ebf7949))\n' +
    '  (fp_arc (start 1.04113 1.079837) (mid 0.000117 1.5) (end -1.040961 1.08)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp 3dd0926c-6c80-4ee8-b980-87b5578d841e))\n' +
    '  (fp_arc (start 1.672335 1.078608) (mid 0.096487 1.987659) (end -1.56 1.235516)\n' +
    '    (stroke (width 0.12) (type solid)) (layer "F.SilkS") (tstamp 7af58d7f-42db-4565-bee2-9da70ccc6bef))\n' +
    '  (fp_line (start -2.42 -2.25) (end -2.42 2.25)\n' +
    '    (stroke (width 0.05) (type solid)) (layer "F.CrtYd") (tstamp e58d5bd5-bdf5-45fd-a86f-c9301b6e7135))\n' +
    '  (fp_line (start -2.42 2.25) (end 2.43 2.25)\n' +
    '    (stroke (width 0.05) (type solid)) (layer "F.CrtYd") (tstamp 736dad6b-1683-41b3-84da-fcad20f5c749))\n' +
    '  (fp_line (start 2.43 -2.25) (end -2.42 -2.25)\n' +
    '    (stroke (width 0.05) (type solid)) (layer "F.CrtYd") (tstamp 097b07f5-03a3-4341-a99c-4f74cd2929ae))\n' +
    '  (fp_line (start 2.43 2.25) (end 2.43 -2.25)\n' +
    '    (stroke (width 0.05) (type solid)) (layer "F.CrtYd") (tstamp 845a0742-2dc8-499b-9eb7-e845009d75d8))\n' +
    '  (fp_line (start -1.5 -1.16619) (end -1.5 1.16619)\n' +
    '    (stroke (width 0.1) (type solid)) (layer "F.Fab") (tstamp 57a49573-76ca-46e4-be0e-bd5c425acd81))\n' +
    '  (fp_arc (start -1.5 -1.16619) (mid 1.9 0.000452) (end -1.500555 1.165476)\n' +
    '    (stroke (width 0.1) (type solid)) (layer "F.Fab") (tstamp 7149b32a-6978-475f-b4ed-80ed66a1fbfe))\n' +
    '  (fp_circle (center 0 0) (end 1.5 0)\n' +
    '    (stroke (width 0.1) (type solid)) (fill none) (layer "F.Fab") (tstamp a66f1ad2-c3c3-4e91-82b1-3f09a31bcbf4))\n' +
    '  (pad "1" thru_hole rect (at -1.27 0) (size 1.8 1.8) (drill 0.9) (layers "*.Cu" "*.Mask") (tstamp 18f4d900-9c25-4a86-8e3d-5550f7b50aa9))\n' +
    '  (pad "2" thru_hole circle (at 1.27 0) (size 1.8 1.8) (drill 0.9) (layers "*.Cu" "*.Mask") (tstamp 3c878d87-71d7-456b-8899-e6d720e61362))\n' +
    '  (model "${KICAD6_3DMODEL_DIR}/LED_THT.3dshapes/LED_D' + diameter + '.0mm.wrl"\n' +
    '    (offset (xyz -1.27 0 0))\n' +
    '    (scale (xyz 1 1 1))\n' +
    '    (rotate (xyz 0 0 0))\n' +
    '  )\n' +
    ')\n\n'
  );
}

// Set custom properties and flush led entity to KiCAD footprint file
function writeKiCADFootprint( led, outputFile ) {
  var x = String( KICAD_OFFSET_MM_FROM_ORIGIN.x + ( led.getCustomProperty( 'QCAD', 'x', null ) * 25.4 ) );
  var y = String( KICAD_OFFSET_MM_FROM_ORIGIN.y + ( Math.abs( led.getCustomProperty( 'QCAD', 'y', null ) * 25.4 ) ) );
  var designator = led.getCustomProperty( 'QCAD', 'designator_lbl', null );
  var diameter = led.getCustomProperty( 'QCAD', 'variant', '3' );
  outputFile.writeString( getKiCADFootprintSection( x, y, designator, diameter ) );
}

// Set designator and KiCAD position, create text label add to QCAD operation
function addEntity( led,
                    objectOperation,
                    labelXOffset,
                    labelYOffset,
                    textHeight,
                    textWidth ) {

  var pos = led.getBoundingBox().getCenter();
  designator++;
  led.setCustomProperty( 'QCAD', 'designator_num', String( designator ) );
  led.setCustomProperty( 'QCAD', 'designator_lbl', DESIGNATOR_PREFIX + designator );
  led.setCustomProperty( 'QCAD', 'x', pos.x );
  led.setCustomProperty( 'QCAD', 'y', pos.y );
  objectOperation.addObject( led );
  pos = new RVector( pos.x + labelXOffset, pos.y + labelYOffset );
  var txtDat = new RTextData( pos,
                              pos,
                              textHeight,
                              textWidth,
                              RS.VAlignBottom,
                              RS.HAlignCenter,
                              RS.LeftToRight,
                              RS.Exact,
                              1.0,
                              String( designator ),
                              'Standard',
                              false,
                              false,
                              ( 0 ),
                              false );
  var txtEnt = new RTextEntity( doc, txtDat );
  opLbl.addObject( txtEnt );
}

// Iterate all entities in the document, delete old designators and process LEDs
objects.forEach( function( id ) {

  var entity = doc.queryEntity( id );
  var layerId = entity.getLayerId();

  if( layerId === designatorsLayer ) {
    opDel.deleteObject( entity ); // < Prune old designators
  }
  else if( entity.getCustomProperty( 'QCAD', 'component', null ) === 'led' ) { // < Only handle LEDs

    if( layerId === dialSecondsLayer ) { // < Outer dial, seconds
      var pos = entity.getBoundingBox().getCenter();
      var rad = Math.atan2( pos.y - docCenter.y, pos.x - docCenter.x );
      var tic = 60 - ( ( 180 + Math.round( RMath.rad2deg( rad ) ) ) + 90 ) / 6;
      if( tic <= 0 ) {
        tic += 60;
      }
      ledsDialSeconds[ tic ] = entity;
    }
    else if( layerId === dialHoursLayer ) { // < Inner dial, hours
      var pos = entity.getBoundingBox().getCenter();
      var rad = Math.atan2( pos.y - docCenter.y, pos.x - docCenter.x );
      var tic = 12 - ( ( 180 + Math.round( RMath.rad2deg( rad ) ) ) + 90 ) / 30;
      if( tic <= 0 ) {
        tic += 60;
      }
      ledsDialHours[ tic ] = entity;
    }
    else if( layerId === dialSeparatorLayer ) { // < Time separator (:)
      var half = entity.getCustomProperty( 'QCAD', 'half', null );
      var i = ( half === 'upper' ? 0 : 1 );
      ledsSeparators[ i ] = entity;
    }
    else if( layerId === dotMatrixLayer ) { // < Number matrices

      var section = entity.getCustomProperty( 'QCAD', 'section', null );

      /* Figure out the correct component designator by organizing the LEDs in a
         multi-dimensional array where the first row is the unit, the second row
         is the digit, then column and row. This mimics the numbering sequence
         in KiCAD */

      var unit = entity.getCustomProperty( 'QCAD', 'unit', null );    // < Exisiting custom property, driver IC (1-2)
      var digit = entity.getCustomProperty( 'QCAD', 'digit', null );  // < Exisiting custom property, digit (0-3)
      var col = entity.getCustomProperty( 'QCAD', 'col', null );      // < Exisiting custom property, column (1-5)
      var row = entity.getCustomProperty( 'QCAD', 'row', null );      // < Exisiting custom property, row (1-7)
      
      if( unit !== null && digit !== null && col !== null && row !== null ) {
        
        if( ledsMatrix[ unit ] === undefined ) {
          ledsMatrix[ unit ] = [ ];
        }
        
        if( ledsMatrix[ unit ][ digit ] === undefined ) {
          ledsMatrix[ unit ][ digit ] = [ ];
        }
        
        if( ledsMatrix[ unit ][ digit ][ col ] === undefined ) {
          ledsMatrix[ unit ][ digit ][ col ] = [ ];
        }
        
        ledsMatrix[ unit ][ digit ][ col ][ row ] = entity;
      }

    }
  }

} );

// Delete old designators
doc.setCurrentLayer( designatorsLayer );
di.applyOperation( opDel );

// Designator counter
var designator = 0;

// Prepare operations to be performed in proper sequence
var opDialSeconds = new RAddObjectsOperation();
var opDialHours = new RAddObjectsOperation();
var opDialSeparator = new RAddObjectsOperation();
var opDotMatrix = new RAddObjectsOperation();
var opLbl = new RAddObjectsOperation();

// Start with Seconds dial, LED 1 to 60
ledsDialSeconds.forEach( function( led, tic ) {
  addEntity( led, opDialSeconds, 0, -0.045, 0.1, 0.2 );
} );

// Hours dial, LED 61 to 72
ledsDialHours.forEach( function( led, tic ) {
  addEntity( led, opDialHours, 0, -0.04, 0.08, 0.15 );
} );

// Do the LED matrices in correct order
ledsMatrix.forEach( function( unit, unitIndex ) {
  unit.forEach( function( digit, digitIndex ) {
    digit.forEach( function( col, colIndex ) {
      col.forEach( function( led, rowIndex ) {
        if( led !== undefined ) {
          addEntity( led, opDotMatrix, 0, -0.025, unitIndex === 1 ? 0.08 : 0.05, unitIndex === 1 ? 0.15 : 0.10 );
        }
      } );
    } );
  } );
} );

// Then the time separator
ledsSeparators.forEach( function( led, tic ) {
  addEntity( led, opDialSeparator, 0, -0.025, 0.05, 0.10 );
} );

// Apply all operations

doc.setCurrentLayer( dotMatrixLayer );
di.applyOperation( opDotMatrix );           // < Commit changes to LED matrices

doc.setCurrentLayer( dialSecondsLayer );
di.applyOperation( opDialSeconds );         // < Commit changes to seconds dial

doc.setCurrentLayer( dialSeparatorLayer );
di.applyOperation( opDialSeparator );       // < Commit changes to time separator

doc.setCurrentLayer( dialHoursLayer );
di.applyOperation( opDialHours );           // < Commit changes to hours dial

doc.setCurrentLayer( designatorsLayer );
di.applyOperation( opLbl );                 // < Commit changes to designator labels

// Create KiCAD export file

var fileName = doc.getFileName();
var fileInfo = new QFileInfo(fileName);
var dir = fileInfo.absolutePath();
var kicdaFileName = dir + '/kicad_pcb.txt';
var kicadFile = new QFile( kicdaFileName );

if( kicadFile.open( QIODevice.WriteOnly ) ) {
    var out = new QTextStream( kicadFile );
    ledsDialSeconds.forEach( function( led ) { // < Seconds dial
      writeKiCADFootprint( led, out );
    } );
    ledsDialHours.forEach( function( led ) {   // < Hours dial
      writeKiCADFootprint( led, out );
    } );
    ledsMatrix.forEach( function( unit ) {     // < LED matrices
      unit.forEach( function( digit ) {
        digit.forEach( function( col ) {
          col.forEach( function( led ) {
            writeKiCADFootprint( led, out );
          } );
        } );
      } );
    } );
    ledsSeparators.forEach( function( led ) {   // < Time separator
      writeKiCADFootprint( led, out );
    } );

    kicadFile.close();  // < Done!
}
else {
    print( "Error: Unable to open " + kicdaFileName + " for writing" );
}

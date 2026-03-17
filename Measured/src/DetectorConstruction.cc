#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4SubtractionSolid.hh"

#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fDetectorVolume(nullptr) 
{
}

DetectorConstruction::~DetectorConstruction() {}

/*
formula:

 G4Tubs* solidShaft2 = new G4Tubs("Shaft2", shaftRadius, shaftRadius + shaftThickness, shaftLength/2, 0.0, 360.0*deg);
    G4LogicalVolume* logicShaft2 = new G4LogicalVolume(solidShaft2, aluminum, "Shaft2");
    G4RotationMatrix* rot2 = new G4RotationMatrix();
    rot2->rotateX(90*deg);
    new G4PVPlacement(rot2, G4ThreeVector(0,-pipeRadius + -shaftLength/2, 0), logicShaft2, "Shaft2", logicWorld, false, 0, true);

    G4VisAttributes* shaft2VisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5)); //r, g, b, transparency
    shaft2VisAtt->SetForceSolid(true);
    logicShaft2->SetVisAttributes(shaft2VisAtt);

*/


G4VPhysicalVolume* DetectorConstruction::Construct()
{

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
    G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");

//--------------------------------------------------------------------------------------

    //world volume:
    G4double worldSize = 2.0*m;
    G4Box* solidWorld = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

//--------------------------------------------------------------------------------------


    //silicon detectors


    G4double detThickness = 1*cm;
    G4double detRadius = 5.0*cm;
    G4Tubs* solidDetector = new G4Tubs("SiDetector", 0.0, detRadius, detThickness/2, 0.0, 360.0*deg);
    fDetectorVolume = new G4LogicalVolume(solidDetector, silicon, "SiDetector");

        //TL
        G4double x1 = -7.969*cm;
        G4double y1 = 13.803*cm;
        G4double z1 = 13.347*cm;
        G4RotationMatrix* rot1 = new G4RotationMatrix();
        rot1->rotateZ(-120.1859*deg);
        rot1->rotateY(131.7030*deg);
        new G4PVPlacement(rot1, G4ThreeVector(x1,y1,z1), fDetectorVolume, "SiDetector", logicWorld, false, 0, true);

        //ML
        G4double x2 = -19.383*cm;
        G4double y2 = 0.0*cm;
        G4double z2 = 8.104*cm;
        G4RotationMatrix* rot2 = new G4RotationMatrix();
        rot2->rotateZ(180.0000*deg);
        rot2->rotateY(114.4731*deg);
        new G4PVPlacement(rot2, G4ThreeVector(x2,y2,z2), fDetectorVolume, "SiDetector", logicWorld, false, 1, true);

        //BL
        G4double x3 = -7.969*cm;
        G4double y3 = -13.803*cm;
        G4double z3 = 13.347*cm;
        G4RotationMatrix* rot3 = new G4RotationMatrix();
        rot3->rotateZ(119.3883*deg);
        rot3->rotateY(131.5054*deg);
        new G4PVPlacement(rot3, G4ThreeVector(x3,y3,z3), fDetectorVolume, "SiDetector", logicWorld, false, 2, true);

        //TR
        G4double x4 = 9.689*cm;
        G4double y4 = 16.782*cm;
        G4double z4 = 8.101*cm;
        G4RotationMatrix* rot4 = new G4RotationMatrix();
        rot4->rotateZ(-59.9473*deg);
        rot4->rotateY(114.4612*deg);
        new G4PVPlacement(rot4, G4ThreeVector(x4,y4,z4), fDetectorVolume, "SiDetector", logicWorld, false, 3, true);

        //MR
        G4double x5 = 16.111*cm;
        G4double y5 = 0.0*cm;
        G4double z5 = 13.483*cm;
        G4RotationMatrix* rot5 = new G4RotationMatrix();
        rot5->rotateY(131.7898*deg);
        new G4PVPlacement(rot5, G4ThreeVector(x5,y5,z5), fDetectorVolume, "SiDetector", logicWorld, false, 4, true);

        //BR
        G4double x6 = 9.689*cm;
        G4double y6 = -16.782*cm;
        G4double z6 = 8.101*cm;
        G4RotationMatrix* rot6 = new G4RotationMatrix();
        rot6->rotateZ(58.9914*deg);
        rot6->rotateY(114.1813*deg);
        new G4PVPlacement(rot6, G4ThreeVector(x6,y6,z6), fDetectorVolume, "SiDetector", logicWorld, false, 5, true);

    G4VisAttributes* detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 1.0));
    detVisAtt->SetForceSolid(true);
    fDetectorVolume->SetVisAttributes(detVisAtt);

//--------------------------------------------------------------------------------------

    //apertures
    G4double discRadius = 5.4925*cm;
    G4double discThickness = 0.635*cm;
    G4Tubs* discSolid = new G4Tubs("Disc", 0, discRadius, discThickness/2, 0, 360*deg);

    G4double holeRadius = 1.25*cm;
    G4double holeRadius2 = 1.57*cm;
    G4Cons* holeSolid = new G4Cons("Hole", 0, holeRadius, 0, holeRadius2, discThickness/2+(0.01*cm), 0, 360*deg);

    G4SubtractionSolid* solidAperture = new G4SubtractionSolid("Aperture", discSolid, holeSolid);
    G4LogicalVolume* logicAperture = new G4LogicalVolume(solidAperture, aluminum, "Aperture");
        
        //TL
        G4double i1 = -7.664*cm;
        G4double j1 = 13.274*cm;
        G4double k1 = 12.862*cm;
        new G4PVPlacement(rot1, G4ThreeVector(i1,j1,k1), logicAperture, "Aperture", logicWorld, false, 0, true);

        //ML
        G4double i2 = -18.451*cm;
        G4double j2 = 0*cm;
        G4double k2 = 7.741*cm;
        new G4PVPlacement(rot2, G4ThreeVector(i2,j2,k2), logicAperture, "Aperture", logicWorld, false, 1, true);
        
        //BL
        G4double i3 = -7.664*cm;
        G4double j3 = -13.274*cm;
        G4double k3 = 12.862*cm;
        new G4PVPlacement(rot3, G4ThreeVector(i3,j3,k3), logicAperture, "Aperture", logicWorld, false, 2, true);

        //TR
        G4double i4 = 9.225*cm;
        G4double j4 = 15.979*cm;
        G4double k4 = 7.741*cm;
        new G4PVPlacement(rot4, G4ThreeVector(i4,j4,k4), logicAperture, "Aperture", logicWorld, false, 3, true);

        //MR
        G4double i5 = 15.328*cm;
        G4double j5 = 0.0*cm;
        G4double k5 = 12.862*cm;
        new G4PVPlacement(rot5, G4ThreeVector(i5,j5,k5), logicAperture, "Aperture", logicWorld, false, 4, true);

        //BR
        G4double i6 = 9.225*cm;
        G4double j6 = -15.979*cm;
        G4double k6 = 7.741*cm;
        new G4PVPlacement(rot6, G4ThreeVector(i6,j6,k6), logicAperture, "Aperture", logicWorld, false, 5, true);

    G4VisAttributes* apertureVisAtt = new G4VisAttributes(G4Color(0.5, 0.5, 0.5, 0.9));
    apertureVisAtt->SetForceSolid(true);
    logicAperture->SetVisAttributes(apertureVisAtt);


    return physWorld;

}

G4LogicalVolume* DetectorConstruction::GetDetectorVolume() const 
{
    return fDetectorVolume;
}

//Bessel function of the first kind
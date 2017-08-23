#include <iostream>
#include "/home/oliver/Programs/gems/gmml/includes/gmml.hpp"
#include "io.h"

using namespace MolecularModeling;

typedef std::vector<Atom*> AtomVector;
typedef std::vector<Residue*> ResidueVector;
typedef std::vector<std::string> StringVector;

double GetDistanceToAtom(Atom *A, Atom *otherAtom);

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    //************************************************//
    // Details for loading in a PDB file              //
    //************************************************//
    std::string working_Directory = Find_Program_Working_Directory();
    std::string installation_Directory = Find_Program_Installation_Directory();
    std::string parameterDirectory = installation_Directory + "/CurrentParams";

    std::vector<std::string> amino_libs, glycam_libs, other_libs, prep;
    amino_libs.push_back(parameterDirectory + "/amino12.lib");
    amino_libs.push_back(parameterDirectory + "/aminoct12.lib");
    amino_libs.push_back(parameterDirectory + "/aminont12.lib");

    glycam_libs.push_back(parameterDirectory + "/GLYCAM_amino_06j_12SB.lib");
    glycam_libs.push_back(parameterDirectory + "/GLYCAM_aminoct_06j_12SB.lib");
    glycam_libs.push_back(parameterDirectory + "/GLYCAM_aminont_06j_12SB.lib");

    other_libs.push_back(parameterDirectory + "/nucleic12.lib");
    other_libs.push_back(parameterDirectory + "/nucleic12.lib");
    other_libs.push_back(parameterDirectory + "/solvents.lib");

    prep.push_back(parameterDirectory + "/GLYCAM_06j-1.prep");

    std::string parameter_file_path = parameterDirectory + "/GLYCAM_06j.dat";
    //std::string ion_parameter_file_path = parameterDirectory + "/atomic_ions.lib";

    //************************************************//
    // Load PDB file                                  //
    //************************************************//
    Assembly assembly;
    assembly.BuildAssemblyFromPdbFile( argv[1], amino_libs, glycam_libs, other_libs, prep, parameter_file_path );
    assembly.BuildStructureByDistance();
    AtomVector cys_atoms, all_SG_atoms;
    ResidueVector residues = assembly.GetAllResiduesOfAssembly();
    // want assembly.GetAllResiduesInSelection(name=CYS,name=CYX);
    // want assembly.GetAllAtomsInSelection(name=SG);
    for (ResidueVector::iterator it = residues.begin(); it != residues.end(); ++it)
    {
        Residue *current_residue = (*it);
        if ( (current_residue->GetName().compare("CYS") == 0) || (current_residue->GetName().compare("CYX") == 0) )
        {
            cys_atoms = current_residue->GetAtoms();
            for (AtomVector::iterator itt = cys_atoms.begin(); itt != cys_atoms.end(); ++itt)
            {
                Atom *atom = (*itt);
                if (atom->GetName().compare("SG") == 0)
                {
                    all_SG_atoms.push_back(atom);
                }
            }
        }
    }
    StringVector atom1ID, atom2ID;
    Atom *atom1, *atom2;
    for (AtomVector::iterator it = all_SG_atoms.begin(); it != all_SG_atoms.end(); ++it)
    {
        atom1 = (*it);
        for (AtomVector::iterator itt = it; itt != all_SG_atoms.end(); ++itt)
        {
            atom2 = (*itt);
            double distance = GetDistanceToAtom(atom1, atom2);
            if ( ( distance < 3.0 ) && ( distance > 0.1 ) )
            {
                atom1ID = split( (atom1->GetId()), '_');
                atom2ID = split( (atom2->GetId()), '_');
                std::cout << "bond mol." << atom1ID.at(4) << ".SG" << " mol." << atom2ID.at(4) << ".SG" << std::endl;
            }
        }
    }
    return 0;
}

double GetDistanceToAtom(Atom *A, Atom *otherAtom)
{
    double x = ( A->GetCoordinates().at(0)->GetX() - otherAtom->GetCoordinates().at(0)->GetX() );
    double y = ( A->GetCoordinates().at(0)->GetY() - otherAtom->GetCoordinates().at(0)->GetY() );
    double z = ( A->GetCoordinates().at(0)->GetZ() - otherAtom->GetCoordinates().at(0)->GetZ() );

    return sqrt( (x*x) + (y*y) + (z*z) );
}


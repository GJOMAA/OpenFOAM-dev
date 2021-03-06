/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::saturationPressureModels::ArdenBuck

Description
    ArdenBuck equation for the vapour pressure of steam.

SourceFiles
    ArdenBuck.C

\*---------------------------------------------------------------------------*/

#ifndef ArdenBuck_H
#define ArdenBuck_H

#include "saturationPressureModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace saturationPressureModels
{

/*---------------------------------------------------------------------------*\
                         Class ArdenBuck Declaration
\*---------------------------------------------------------------------------*/

class ArdenBuck
:
    public saturationPressureModel
{
private:

    // Private Member Functions

        //- Exponent divided by the temperature
        tmp<volScalarField> xByTC(const volScalarField& TC) const;


public:

    //- Runtime type information
    TypeName("ArdenBuck");

    // Constructors

        //- Construct from a dictionary
        ArdenBuck(const dictionary& dict);


    //- Destructor
    virtual ~ArdenBuck();


    // Member Functions

        //- Saturation pressure
        virtual tmp<volScalarField> pSat(const volScalarField& T) const;

        //- Saturation pressure derivetive w.r.t. temperature
        virtual tmp<volScalarField> pSatPrime(const volScalarField& T) const;

        //- Natural log of the saturation pressure
        virtual tmp<volScalarField> lnPSat(const volScalarField& T) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace saturationPressureModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

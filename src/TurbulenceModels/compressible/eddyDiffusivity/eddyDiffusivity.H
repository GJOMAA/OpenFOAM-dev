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
    Foam::eddyDiffusivity

Description
    Templated abstract base class for single-phase compressible
    turbulence models.

SourceFiles
    eddyDiffusivity.C

\*---------------------------------------------------------------------------*/

#ifndef eddyDiffusivity_H
#define eddyDiffusivity_H

#include "CompressibleTurbulenceModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
               Class eddyDiffusivity Declaration
\*---------------------------------------------------------------------------*/

template<class BasicTurbulenceModel>
class eddyDiffusivity
:
    public BasicTurbulenceModel
{

protected:

    // Protected data

        // Model coefficients

            dimensionedScalar Prt_;

        // Fields

            volScalarField alphat_;


    // Protected Member Functions

        virtual void correctNut();


public:

    typedef typename BasicTurbulenceModel::alphaField alphaField;
    typedef typename BasicTurbulenceModel::rhoField rhoField;
    typedef typename BasicTurbulenceModel::transportModel transportModel;


    // Constructors

        //- Construct
        eddyDiffusivity
        (
            const word& type,
            const geometricOneField& alpha,
            const volScalarField& rho,
            const volVectorField& U,
            const surfaceScalarField& alphaRhoPhi,
            const surfaceScalarField& phi,
            const transportModel& trasport,
            const word& propertiesName
        );


    // Selectors

        //- Return a reference to the selected turbulence model
        static autoPtr<eddyDiffusivity> New
        (
            const volScalarField& rho,
            const volVectorField& U,
            const surfaceScalarField& phi,
            const transportModel& trasportModel,
            const word& propertiesName = turbulenceModel::propertiesName
        );


    //- Destructor
    virtual ~eddyDiffusivity()
    {}


    // Member Functions

        //- Re-read model coefficients if they have changed
        virtual bool read();

        //- Return the turbulent thermal diffusivity for enthalpy [kg/m/s]
        virtual tmp<volScalarField> alphat() const
        {
            return alphat_;
        }

        //- Return the turbulent thermal diffusivity for enthalpy for a patch
        //  [kg/m/s]
        virtual tmp<scalarField> alphat(const label patchi) const
        {
            return alphat()().boundaryField()[patchi];
        }

        //- Return the effective turbulent thermal diffusivity for temperature
        //  [J/m/s/K]
        virtual tmp<volScalarField> kappaEff() const
        {
            return this->transport_.kappaEff(alphat());
        }

        //- Return the effective turbulent thermal diffusivity for temperature
        //  [J/m/s/K]
        virtual tmp<scalarField> kappaEff(const label patchi) const
        {
            return this->transport_.kappaEff(alphat(patchi), patchi);
        }

        //- Return the effective turbulent thermal diffusivity for enthalpy
        //  [kg/m/s]
        virtual tmp<volScalarField> alphaEff() const
        {
            return this->transport_.alphaEff(alphat());
        }

        //- Return the effective turbulent thermal diffusivity for enthalpy
        //  for a patch [kg/m/s]
        virtual tmp<scalarField> alphaEff(const label patchi) const
        {
            return this->transport_.alphaEff(alphat(patchi), patchi);
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "eddyDiffusivity.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

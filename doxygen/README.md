# Merlin Doxygen Generation

These instructions will (in the future) tell you how to generate your own
`doxygen` files for `Merlin`

## Viewing the Documentation

If you wish to view pre-generated documentation, they are *temporarily*
being hosted at [http://users.ox.ac.uk/~scat6524/merlin-doxygen/html](
http://users.ox.ac.uk/~scat6524/merlin-doxygen/html/index.html)

To compile and view your own documentation, download all of the files in the
`doxygen` folder, run `doxygen Merlin.Doxyfile`, then open a page (e.g.
`index.html`) in `generated-docs/html`

Man-pages and pdf-diagrams can be found and viewed in a similar manner, under
the folders `doxygen/generated-docs/man/man3` and 
`doxygen/generated-docs/latex` respectively. 

*Note: to view the man pages, run the command*
`man $PATH_TO_MAN_PAGES/the_page.3` or `man ,/the_page.3` *if you are in the 
man page directory*.

## Editing the Documentation

The main documentation file is under `Merlin/Documentation.cpp`

If you wish to familiarise yourself with `doxygen`, the [Doxygen website
](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html) is a great place
to start

To generate `doxygen` files, ensure you are in the `doxygen` directory, in which
`Merlin.Doxyfile` is contained, then run `doxygen Merlin.Doxyfile`. 

## Source File Documentation Status

In the table below, we list the extent of doxygen-compatible documentation
implemented in each source file. A checkmark (✓) indicates that obvious changes
to the code (e.g. converting double slashes into triple) for compatibility have
been implemented but does not indicate the existence of satisfactory (or any)
actual documentation. A description (excellent/good/satisfactory/poor/etc.) is
used to mark the amount/condition of documentation in that file. As header files
define the member functions and `cpp` files implement them, we won't need much
(if any) documentation in most `cpp` files.

Classification (rough guide):

* Excellent: uses doxygen specific syntax such as `@return` and `@param`, and
contains complete description of code

* Good: May limited doxygen specific syntax, has sufficient description of code

* Satisfactory: Contains partial description of the code, but doesn't make use
of doxygen specific syntax such as `@return` 

* Poor: Not enough documentation

* No documentation

* Complete: This file doesn't need documenting/has all necessary documentation
and shouldn't be altered

| Source File                     | Recent Check for *some* `doxygen` documentation? | Date of Check |
|---------------------------------|--------------------------------------------------|---------------|
| AcceleratorComponent.h          | Excellent                                        | 2017-08-04    |
| AcceleratorErrors.h             | Excellent                                        | 2017-08-04    |
| AcceleratorGeometry.h           | Excellent                                        | 2017-08-04    |
| AcceleratorModelConstructor.h   | Good                                             | 2017-08-07    |
| AcceleratorModel.h              | Excellent                                        | 2017-08-04    |
| AcceleratorSupport.h            | Good                                             | 2017-08-07    |
| ACG.h                           | Satisfactory                                     | 2017-08-07    |
| algorithm.h                     | No documentation                                 | 2017-08-04    |
| AMBufferManager.h               | Good                                             | 2017-08-07    |
| ApertureConfiguration.h         | Excellent                                        | 2017-08-04    |
| Aperture.h                      | Excellent                                        | 2017-08-04    |
| ApertureSurvey.h                | Excellent                                        | 2017-08-04    |
| ArcGeometry.h                   | Good                                             | 2017-08-07    |
| ArcMultipoleField.h             | Good                                             | 2017-08-04    |
| ATL2D.h                         | Good                                             | 2017-08-04    |
| AxisRotations.h                 | Satisfactory                                     | 2017-08-04    |
| BasicTransportMaps.h            | Poor                                             | 2017-08-04    |
| BeamData.h                      | Poor                                             | 2017-08-04    |
| BetatronTunes.h                 | No documentation                                 | 2017-08-04    |
| BetatronTunes.h.2               | No documentation                                 | 2017-08-04    |
| Binomial.h                      | No documentation                                 | 2017-08-04    |
| BPMChannelCtor.h                | Satisfactory                                     | 2017-08-04    |
| BPMChannel.h                    | Satisfactory                                     | 2017-08-04    |
| BPMDataBuffer.h                 | Satisfactory                                     | 2017-08-04    |
| BPMDataBufferServer.h           | Poor                                             | 2017-08-04    |
| BPM.h                           | Satisfactory                                     | 2017-08-04    |
| BunchConstructor.h              | Satisfactory                                     | 2017-08-04    |
| BunchConverter.h                | Good                                             | 2017-08-04    |
| BunchFilter.h                   | Poor                                             | 2017-08-04    |
| Bunch.h                         | Satisfactory                                     | 2017-08-04    |
| BunchProcess.h                  | Poor (some single comments describe multiple fns)|               |
| BzField.h                       | Satisfactory                                     | 2017-08-04    |
| CCFailureProcess.h              | Satisfactory (but some comments need splitting)  | 2017-08-04    |
| CenteredGeometry.h              | Good                                             | 2017-08-04    |
| ChannelServer.h                 | Satisfactory                                     | 2017-08-04    |
| Channels.h                      | Good                                             | 2017-08-04    |
| ClosedOrbit.h                   | No documentation                                 | 2017-08-04    |
| CollimateParticleProcess.h      | Satisfactory                                     | 2017-08-04    |
| CollimateProtonProcess.h        | Good                                             | 2017-08-04    |
| CollimationOutput.h             | Satisfactory                                     | 2017-08-04    |
| CollimatorAperture.h            | Poor                                             | 2017-08-04    |
| CollimatorDatabase.h            | Poor                                             | 2017-08-04    |
| Collimator.h                    | Good                                             | 2017-08-04    |
| CollimatorPotentialModels.h     | Poor                                             | 2017-08-04    |
| CollimatorTable.h               | No documentation                                 | 2017-08-04    |
| CollimatorWakePotentials.h      | No documentation                                 | 2017-08-04    |
| CollimatorWakeProcess.h         | Poor                                             | 2017-08-04    |
| CombinedWakeRF.h                | Poor                                             | 2017-08-04    |
| ComplexDef.h                    | No documentation                                 | 2017-08-04    |
| Complex.h                       | No documentation                                 | 2017-08-04    |
| ComponentFrame.h                | Satisfactory                                     | 2017-08-04    |
| ComponentIntegrator.h           | Satisfactory                                     | 2017-08-04    |
| Components.h                    | Complete                                         | 2017-08-04    |
| ComponentStepper.h              | Lots of weird numbers...                         | 2017-08-04    |
| ComponentTracker.h              | Good                                             | 2017-08-07    |
| CompositeMaterial.h             | Satisfactory                                     | 2017-08-07    |
| ConstructSrot.h                 | Poor                                             | 2017-08-07    |
| CorrectorDipoles.h              | Satisfactory                                     | 2017-08-07    |
| CorrectorWinding.h              | Satisfactory                                     | 2017-08-07    |
| CoulombScatter.h                | Satisfactory                                     | 2017-08-07    |
| CouplerWakeFieldProcess.h       | Satisfactory                                     | 2017-08-07    |
| CPUFeatures.h                   | Good                                             | 2017-08-07    |
| CrabMarker.h                    | Poor                                             | 2017-08-07    |
| CrossSections.h                 | No documentation                                 | 2017-08-07    |
| deleters.h                      | Good                                             | 2017-08-07    |
| DiffractiveScatter.h            | Excellent                                        | 2017-08-07    |
| DiscUnif.h                      | No documentation                                 | 2017-08-07    |
| Dispersion.h                    | No documentation                                 | 2017-08-07    |
| Drift.h                         | Good                                             | 2017-08-07    |
| DynamicModel.h                  | Complete                                         | 2017-08-07    |
| echo_ostream.h                  | Satisfactory                                     | 2017-08-07    |
| ElasticScatter.h                |                                                  |               |
| ElectronBunch.h                 |                                                  |               |
| ElementRepository.h             |                                                  |               |
| EMField.h                       |                                                  |               |
| EquilibriumDistribution.h       |                                                  |               |
| Erlang.h                        |                                                  |               |
| FlukaCollimationOutput.h        |                                                  |               |
| FrameModifier.h                 |                                                  |               |
| GeneralRotation.h               |                                                  |               |
| GeometryObject3D.h              |                                                  |               |
| GeometryPatch.h                 |                                                  |               |
| Geom.h                          |                                                  |               |
| Histogram.h                     |                                                  |               |
| HollowElectronLens.h            |                                                  |               |
| HollowELensProcess.h            |                                                  |               |
| HypGeom.h                       |                                                  |               |
| IdentityRotation.h              |                                                  |               |
| IndirectChannels.h              |                                                  |               |
| InterpolatedApertures.h         |                                                  |               |
| Interpolation.h                 |                                                  |               |
| Klystron.h                      |                                                  |               |
| Landau.h                        |                                                  |               |
| LatticeFrame.h                  |                                                  |               |
| LatticeFunctions.h              |                                                  |               |
| LCAVintegrator.h                |                                                  |               |
| LinearAlgebra.h                 |                                                  |               |
| LinearFBSystem.h                |                                                  |               |
| LinearParticleMap.h             |                                                  |               |
| LogNorm.h                       |                                                  |               |
| LossMapCollimationOutput.h      |                                                  |               |
| MADInterface.h                  |                                                  |               |
| MADKeyMap.h                     |                                                  |               |
| MagnetMover.h                   |                                                  |               |
| Marker.h                        |                                                  |               |
| MaterialDatabase.h              |                                                  |               |
| Material.h                      |                                                  |               |
| MaterialMixture.h               |                                                  |               |
| MatrixMaps.h                    |                                                  |               |
| MatrixPrinter.h                 |                                                  |               |
| Measurement.h                   |                                                  |               |
| merlin_config.h                 |                                                  |               |
| MerlinException.h               |                                                  |               |
| MerlinIO.h                      |                                                  |               |
| MerlinProfile.h                 |                                                  |               |
| MLCG.h                          |                                                  |               |
| ModelElement.h                  |                                                  |               |
| Monitor.h                       |                                                  |               |
| MonitorProcess.h                |                                                  |               |
| MultiNormal.h                   |                                                  |               |
| MultipoleField.h                |                                                  |               |
| MuonBunch.h                     |                                                  |               |
| MVCMatrix.h                     |                                                  |               |
| NANCheckProcess.h               |                                                  |               |
| NegExp.h                        |                                                  |               |
| Normal.h                        |                                                  |               |
| NormalTransform.h               |                                                  |               |
| NumericalConstants.h            |                                                  |               |
| OPFormat.h                      |                                                  |               |
| ParticleBunchConstructor.h      |                                                  |               |
| ParticleBunch.h                 |                                                  |               |
| ParticleBunchProcess.h          |                                                  |               |
| ParticleBunchTypes.h            |                                                  |               |
| ParticleBunchUtilities.h        |                                                  |               |
| ParticleComponentTracker.h      |                                                  |               |
| ParticleMapComponent.h          |                                                  |               |
| ParticleMap.h                   |                                                  |               |
| ParticleMapPI.h                 |                                                  |               |
| ParticleTracker.h               |                                                  |               |
| PatchFrame.h                    |                                                  |               |
| PhaseAdvance.h                  |                                                  |               |
| PhysicalConstants.h             |                                                  |               |
| PhysicalUnits.h                 |                                                  |               |
| Poisson.h                       |                                                  |               |
| ProcessStepManager.h            |                                                  |               |
| ProtonBunch.h                   |                                                  |               |
| PSmoments.h                     |                                                  |               |
| PSTypes.h                       |                                                  |               |
| PSvector.h                      |                                                  |               |
| PSvectorTransform3D.h           |                                                  |               |
| Random.h                        |                                                  |               |
| RandomNG.h                      |                                                  |               |
| Range.h                         |                                                  |               |
| RectangularGeometry.h           |                                                  |               |
| RectEllipseAperture.h           |                                                  |               |
| RectMultipoleField.h            |                                                  |               |
| RectMultipole.h                 |                                                  |               |
| RectSWRF.h                      |                                                  |               |
| RectTWRF.h                      |                                                  |               |
| ReferenceParticle.h             |                                                  |               |
| ResistiveWakePotentials.h       |                                                  |               |
| RFAcceleratingField.h           |                                                  |               |
| RFStructure.h                   |                                                  |               |
| RingDeltaTProcess.h             |                                                  |               |
| ring_iterator.h                 |                                                  |               |
| RMap.h                          |                                                  |               |
| RMSProfileMonitor.h             |                                                  |               |
| RndInt.h                        |                                                  |               |
| RNG.h                           |                                                  |               |
| Rot3Drep.h                      |                                                  |               |
| Rotation3D.h                    |                                                  |               |
| RotationMatrix.h                |                                                  |               |
| RotationType.h                  |                                                  |               |
| RTMap.h                         |                                                  |               |
| RWChannelState.h                |                                                  |               |
| ScatteringModel.h               |                                                  |               |
| ScatteringModelsMerlin.h        |                                                  |               |
| ScatteringProcess.h             |                                                  |               |
| ScatterProton.h                 |                                                  |               |
| SectorBend.h                    |                                                  |               |
| SequenceFrame.h                 |                                                  |               |
| SimpleApertures.h               |                                                  |               |
| SimpleATL.h                     |                                                  |               |
| SimpleDrift.h                   |                                                  |               |
| SimpleSolenoid.h                |                                                  |               |
| SliceMacroParticle.h            |                                                  |               |
| SMPBunchConstructor.h           |                                                  |               |
| SMPBunch.h                      |                                                  |               |
| SMPBunchProcess.h               |                                                  |               |
| SMPComponentTracker.h           |                                                  |               |
| SMPStdIntegrators.h             |                                                  |               |
| SMPTracker.h                    |                                                  |               |
| SMPTransform3D.h                |                                                  |               |
| SMPWakeFieldProcess.h           |                                                  |               |
| Solenoid.h                      |                                                  |               |
| Space2D.h                       |                                                  |               |
| Space3D.h                       |                                                  |               |
| SpinParticleProcess.h           |                                                  |               |
| StableOrbits.h                  |                                                  |               |
| StandardMultipoles.h            |                                                  |               |
| StdIntegrators.h                |                                                  |               |
| StringPattern.h                 |                                                  |               |
| SupportStructure.h              |                                                  |               |
| svdcmp.h                        |                                                  |               |
| SWRFfield.h                     |                                                  |               |
| SWRFStructure.h                 |                                                  |               |
| SymplecticIntegrators.h         |                                                  |               |
| SynchRadParticleProcess.h       |                                                  |               |
| TaperedCollimatorPotentials.h   |                                                  |               |
| tblas.h                         |                                                  |               |
| TComponentFrame.h               |                                                  |               |
| TCovMtrx.h                      |                                                  |               |
| TemplateComponents.h            |                                                  |               |
| Timing.h                        |                                                  |               |
| TLAS.h                          |                                                  |               |
| TLASimp.h                       |                                                  |               |
| TMatrixLib.h                    |                                                  |               |
| TrackingOutputAV.h              |                                                  |               |
| TrackingSimulation.h            |                                                  |               |
| TransferMatrix.h                |                                                  |               |
| Transform2D.h                   |                                                  |               |
| Transform3D.h                   |                                                  |               |
| Transformable.h                 |                                                  |               |
| TransportMatrix.h               |                                                  |               |
| TransportRMap.h                 |                                                  |               |
| TransRFfield.h                  |                                                  |               |
| TransRFIntegrator.h             |                                                  |               |
| TransverseRFStructure.h         |                                                  |               |
| TTrackSim.h                     |                                                  |               |
| TWRFfield.h                     |                                                  |               |
| TWRFStructure.h                 |                                                  |               |
| Uniform.h                       |                                                  |               |
| utils.h                         |                                                  |               |
| VectorTags.h                    |                                                  |               |
| WakeFieldProcess.h              |                                                  |               |
| WakePotentials.h                |                                                  |               |
| Weibull.h                       |                                                  |               |
| XTFFInterface.h                 |                                                  |               |

# Merlin Doxygen Generation

These instructions are give for you to generate your own `doxygen` files for
`Merlin`

## Viewing the Documentation

If you wish to view pre-generated documentation, they are *temporarily*
being hosted at <http://users.ox.ac.uk/~scat6524/merlin-doxygen/html> and a PDF
copy at <http://users.ox.ac.uk/~scat6524/merlin-doxygen/latex/refman.pdf>

To compile documentation yourself, download all of the files in the `doxygen`
folder, run `doxygen Merlin.Doxyfile`, then open a page (e.g. `index.html`) in
`generated-docs/html`

Man-pages and pdf-diagrams can be found and viewed in a similar manner, under
the folders `doxygen/generated-docs/man/man3` and 
`doxygen/generated-docs/latex` respectively. 

To generate the PDF manual, `cd` into the `latex` sub-directory and run `make`.
This will generate `refman.pdf`.

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
| AxisRotations.h                 | Good                                             | 2017-08-07    |
| BasicTransportMaps.h            | No documentation                                 | 2017-08-07    |
| BeamData.h                      | Satisfactory                                     | 2017-08-07    |
| BetatronTunes.h                 | No documentation                                 | 2017-08-04    |
| BetatronTunes.h.2               | No documentation                                 | 2017-08-04    |
| Binomial.h                      | No documentation                                 | 2017-08-04    |
| BPMChannelCtor.h                | Good                                             | 2017-08-07    |
| BPMChannel.h                    | Good                                             | 2017-08-07    |
| BPMDataBuffer.h                 | Satisfactory                                     | 2017-08-07    |
| BPMDataBufferServer.h           | Satisfactory                                     | 2017-08-07    |
| BPM.h                           | Satisfactory                                     | 2017-08-04    |
| BunchConstructor.h              | Satisfactory                                     | 2017-08-04    |
| BunchConverter.h                | Good                                             | 2017-08-04    |
| BunchFilter.h                   | Poor                                             | 2017-08-04    |
| Bunch.h                         | Satisfactory                                     | 2017-08-04    |
| BunchProcess.h                  | Poor (some single comments describe multiple fns)| 2017-08-07    |
| BzField.h                       | Good                                             | 2017-08-07    |
| CCFailureProcess.h              | Satisfactory                                     | 2017-08-07    |
| CenteredGeometry.h              | Good                                             | 2017-08-07    |
| ChannelServer.h                 | Good                                             | 2017-08-07    |
| Channels.h                      | Good                                             | 2017-08-07    |
| ClosedOrbit.h                   | No documentation                                 | 2017-08-04    |
| CollimateParticleProcess.h      | Satisfactory                                     | 2017-08-07    |
| CollimateProtonProcess.h        | Good                                             | 2017-08-07    |
| CollimationOutput.h             | Satisfactory                                     | 2017-08-07    |
| CollimatorAperture.h            | Poor                                             | 2017-08-07    |
| CollimatorDatabase.h            | Satisfactory                                     | 2017-08-07    |
| Collimator.h                    | Good                                             | 2017-08-07    |
| CollimatorPotentialModels.h     | Poor                                             | 2017-08-07    |
| CollimatorTable.h               | No documentation                                 | 2017-08-04    |
| CollimatorWakePotentials.h      | No documentation                                 | 2017-08-04    |
| CollimatorWakeProcess.h         | Poor                                             | 2017-08-08    |
| CombinedWakeRF.h                | Poor, ref TWRFStructure::GetPhase doesn't exist  | 2017-08-08    |
| ComplexDef.h                    | No documentation                                 | 2017-08-04    |
| Complex.h                       | No documentation                                 | 2017-08-04    |
| ComponentFrame.h                | Satisfactory                                     | 2017-08-08    |
| ComponentIntegrator.h           | Satisfactory                                     | 2017-08-08    |
| Components.h                    | Complete                                         | 2017-08-04    |
| ComponentStepper.h              | Lots of weird numbers and symbols                | 2017-08-08    |
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
| ElasticScatter.h                | Good                                             | 2017-08-08    |
| ElectronBunch.h                 | Satisfactory                                     | 2017-08-08    |
| ElementRepository.h             | Good                                             | 2017-08-08    |
| EMField.h                       | Excellent                                        | 2017-08-08    |
| EquilibriumDistribution.h       | No documentation                                 | 2017-08-08    |
| Erlang.h                        | No documentation                                 | 2017-08-08    |
| FlukaCollimationOutput.h        | No documentation                                 | 2017-08-08    |
| FrameModifier.h                 | Good                                             | 2017-08-08    |
| GeneralRotation.h               | Good                                             | 2017-08-08    |
| GeometryObject3D.h              | Good                                             | 2017-08-08    |
| GeometryPatch.h                 | Satisfactory                                     | 2017-08-08    |
| Geom.h                          | No documentation                                 | 2017-08-08    |
| Histogram.h                     | No documentation                                 | 2017-08-08    |
| HollowElectronLens.h            | Satisfactory                                     | 2017-08-08    |
| HollowELensProcess.h            | Good                                             | 2017-08-08    |
| HypGeom.h                       | No documentation                                 | 2017-08-08    |
| IdentityRotation.h              | Good                                             | 2017-08-08    |
| IndirectChannels.h              | Good                                             | 2017-08-08    |
| InterpolatedApertures.h         | Satisfactory                                     | 2017-08-08    |
| Interpolation.h                 | Satisfactory                                     | 2017-08-08    |
| Klystron.h                      | Satisfactory                                     | 2017-08-08    |
| Landau.h                        | No documentation                                 | 2017-08-08    |
| LatticeFrame.h                  | Good                                             | 2017-08-08    |
| LatticeFunctions.h              | No documentation                                 | 2017-08-08    |
| LCAVintegrator.h                | No documentation                                 | 2017-08-08    |
| LinearAlgebra.h                 | Satisfactory                                     | 2017-08-08    |
| LinearFBSystem.h                | Poor                                             | 2017-08-08    |
| LinearParticleMap.h             | Poor                                             | 2017-08-08    |
| LogNorm.h                       | No documentation                                 | 2017-08-08    |
| LossMapCollimationOutput.h      | Excellent                                        | 2017-08-08    |
| MADInterface.h                  | Good                                             | 2017-08-08    |
| MADKeyMap.h                     | Good                                             | 2017-08-08    |
| MagnetMover.h                   | Good                                             | 2017-08-08    |
| Marker.h                        | Good                                             | 2017-08-08    |
| MaterialDatabase.h              | Satisfactory                                     | 2017-08-08    |
| Material.h                      | Satisfactory                                     | 2017-08-08    |
| MaterialMixture.h               | Satisfactory                                     | 2017-08-08    |
| MatrixMaps.h                    | Good                                             | 2017-08-08    |
| MatrixPrinter.h                 | Complete                                         | 2017-08-08    |
| Measurement.h                   | Poor                                             | 2017-08-08    |
| merlin_config.h                 | Complete                                         | 2017-08-08    |
| MerlinException.h               | Excellent                                        | 2017-08-08    |
| MerlinIO.h                      | Poor                                             | 2017-08-08    |
| MerlinProfile.h                 | Poor                                             | 2017-08-08    |
| MLCG.h                          | Poor                                             | 2017-08-08    |
| ModelElement.h                  | Excellent                                        | 2017-08-08    |
| Monitor.h                       | Good                                             | 2017-08-08    |
| MonitorProcess.h                | Excellent                                        | 2017-08-08    |
| MultiNormal.h                   | Poor                                             | 2017-08-08    |
| MultipoleField.h                | Good                                             | 2017-08-08    |
| MuonBunch.h                     | Good                                             | 2017-08-08    |
| MVCMatrix.h                     | Good                                             | 2017-08-08    |
| NANCheckProcess.h               | No documentation                                 | 2017-08-08    |
| NegExp.h                        | No documentation                                 | 2017-08-08    |
| Normal.h                        | No documentation                                 | 2017-08-08    |
| NormalTransform.h               | No documentation                                 | 2017-08-08    |
| NumericalConstants.h            | Complete                                         | 2017-08-08    |
| OPFormat.h                      | Poor                                             | 2017-08-08    |
| ParticleBunchConstructor.h      | Good                                             | 2017-08-08    |
| ParticleBunch.h                 | Good                                             | 2017-08-08    |
| ParticleBunchProcess.h          | Complete                                         | 2017-08-08    |
| ParticleBunchTypes.h            | Complete                                         | 2017-08-08    |
| ParticleBunchUtilities.h        | Excellent                                        | 2017-08-08    |
| ParticleComponentTracker.h      | Complete                                         | 2017-08-08    |
| ParticleMapComponent.h          | Good                                             | 2017-08-08    |
| ParticleMap.h                   | Satisfactory                                     | 2017-08-08    |
| ParticleMapPI.h                 | Poor                                             | 2017-08-08    |
| ParticleTracker.h               | Good                                             | 2017-08-08    |
| PatchFrame.h                    | Poor, also code labeled as needing rewrite       | 2017-08-08    |
| PhaseAdvance.h                  | Satisfactory                                     | 2017-08-08    |
| PhysicalConstants.h             | Complete                                         | 2017-08-08    |
| PhysicalUnits.h                 | Complete                                         | 2017-08-08    |
| Poisson.h                       | No documentation                                 | 2017-08-08    |
| ProcessStepManager.h            | Good                                             | 2017-08-08    |
| ProtonBunch.h                   | Poor                                             | 2017-08-08    |
| PSmoments.h                     | Poor                                             | 2017-08-08    |
| PSTypes.h                       | Complete                                         | 2017-08-08    |
| PSvector.h                      | Poor                                             | 2017-08-08    |
| PSvectorTransform3D.h           | Poor                                             | 2017-08-08    |
| Random.h                        | No documentation                                 | 2017-08-08    |
| RandomNG.h                      | Good                                             | 2017-08-08    |
| Range.h                         | Satisfactory                                     | 2017-08-08    |
| RectangularGeometry.h           | Good                                             | 2017-08-08    |
| RectEllipseAperture.h           | Satisfactory                                     | 2017-08-08    |
| RectMultipoleField.h            | Good                                             | 2017-08-08    |
| RectMultipole.h                 | Good                                             | 2017-08-08    |
| RectSWRF.h                      | Good                                             | 2017-08-08    |
| RectTWRF.h                      | Good                                             | 2017-08-08    |
| ReferenceParticle.h             | Good                                             | 2017-08-08    |
| ResistiveWakePotentials.h       | No documentation                                 | 2017-08-08    |
| RFAcceleratingField.h           | Good                                             | 2017-08-08    |
| RFStructure.h                   | Good                                             | 2017-08-08    |
| RingDeltaTProcess.h             | No documentation                                 | 2017-08-08    |
| ring_iterator.h                 | Poor                                             | 2017-08-08    |
| RMap.h                          | Satisfactory                                     | 2017-08-08    |
| RMSProfileMonitor.h             | Poor                                             | 2017-08-08    |
| RndInt.h                        | Satisfactory                                     | 2017-08-08    |
| RNG.h                           | Poor                                             | 2017-08-08    |
| Rot3Drep.h                      | Good                                             | 2017-08-08    |
| Rotation3D.h                    | Good, but suspiciously similar to Rot3Drep.h...  | 2017-08-08    |
| RotationMatrix.h                | Poor                                             | 2017-08-08    |
| RotationType.h                  | Complete                                         | 2017-08-08    |
| RTMap.h                         | Satisfactory                                     | 2017-08-08    |
| RWChannelState.h                | No documentation                                 | 2017-08-08    |
| ScatteringModel.h               | Poor                                             | 2017-08-08    |
| ScatteringModelsMerlin.h        | Good                                             | 2017-08-08    |
| ScatteringProcess.h             | Poor                                             | 2017-08-08    |
| ScatterProton.h                 | Complete                                         | 2017-08-08    |
| SectorBend.h                    | Satisfactory                                     | 2017-08-08    |
| SequenceFrame.h                 | Satisfactory                                     | 2017-08-08    |
| SimpleApertures.h               | Satisfactory                                     | 2017-08-10    |
| SimpleATL.h                     | Satisfactory                                     | 2017-08-10    |
| SimpleDrift.h                   | Complete                                         | 2017-08-10    |
| SimpleSolenoid.h                | No documentation                                 | 2017-08-10    |
| SliceMacroParticle.h            | Poor                                             | 2017-08-10    |
| SMPBunchConstructor.h           | Satisfactory                                     | 2017-08-10    |
| SMPBunch.h                      | Satisfactory                                     | 2017-08-10    |
| SMPBunchProcess.h               | No documentation                                 | 2017-08-10    |
| SMPComponentTracker.h           | Complete                                         | 2017-08-10    |
| SMPStdIntegrators.h             | Poor                                             | 2017-08-10    |
| SMPTracker.h                    | No documentation                                 | 2017-08-10    |
| SMPTransform3D.h                | Poor                                             | 2017-08-10    |
| SMPWakeFieldProcess.h           | Poor                                             | 2017-08-10    |
| Solenoid.h                      | Good                                             | 2017-08-10    |
| Space2D.h                       | Satisfactory                                     | 2017-08-10    |
| Space3D.h                       | Satisfactory                                     | 2017-08-10    |
| SpinParticleProcess.h           | Poor                                             | 2017-08-10    |
| StableOrbits.h                  | No documentation                                 | 2017-08-10    |
| StandardMultipoles.h            | Satisfactory                                     | 2017-08-10    |
| StdIntegrators.h                | No documentation                                 | 2017-08-10    |
| StringPattern.h                 | Satisfactory                                     | 2017-08-10    |
| SupportStructure.h              | Good                                             | 2017-08-10    |
| svdcmp.h                        | No documentation                                 | 2017-08-10    |
| SWRFfield.h                     | Satisfactory                                     | 2017-08-10    |
| SWRFStructure.h                 | Satisfactory                                     | 2017-08-10    |
| SymplecticIntegrators.h         | No documentation                                 | 2017-08-10    |
| SynchRadParticleProcess.h       | Good                                             | 2017-08-10    |
| TaperedCollimatorPotentials.h   | No documentation                                 | 2017-08-10    |
| tblas.h                         | Poor documentation, and the code wants a rewrite | 2017-08-10    |
| TComponentFrame.h               | Poor                                             | 2017-08-10    |
| TCovMtrx.h                      | Poor                                             | 2017-08-10    |
| TemplateComponents.h            | Poor                                             | 2017-08-10    |
| Timing.h                        | No documentation                                 | 2017-08-10    |
| TLAS.h                          | Poor                                             | 2017-08-10    |
| TLASimp.h                       | Poor, and a lot of code in header file (move it?)| 2017-08-10    |
| TMatrixLib.h                    | Satisfactory                                     | 2017-08-10    |
| TrackingOutputAV.h              | Poor                                             | 2017-08-11    |
| TrackingSimulation.h            | Good                                             | 2017-08-11    |
| TransferMatrix.h                | No documentation                                 | 2017-08-11    |
| Transform2D.h                   | Good                                             | 2017-08-11    |
| Transform3D.h                   | Satisfactory                                     | 2017-08-11    |
| Transformable.h                 | Satisfactory                                     | 2017-08-11    |
| TransportMatrix.h               | Good                                             | 2017-08-11    |
| TransportRMap.h                 | No documentation                                 | 2017-08-11    |
| TransRFfield.h                  | Good                                             | 2017-08-11    |
| TransRFIntegrator.h             | No documentation                                 | 2017-08-11    |
| TransverseRFStructure.h         | Satisfactory                                     | 2017-08-11    |
| TTrackSim.h                     | Good                                             | 2017-08-11    |
| TWRFfield.h                     | Good                                             | 2017-08-11    |
| TWRFStructure.h                 | Good                                             | 2017-08-11    |
| Uniform.h                       | Poor                                             | 2017-08-11    |
| utils.h                         | Poor                                             | 2017-08-11    |
| VectorTags.h                    | Good                                             | 2017-08-11    |
| WakeFieldProcess.h              | Poor                                             | 2017-08-11    |
| WakePotentials.h                | Poor                                             | 2017-08-11    |
| Weibull.h                       | No documentation                                 | 2017-08-11    |
| XTFFInterface.h                 | Satisfactory                                     | 2017-08-11    |

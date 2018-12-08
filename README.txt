/*
    NHC - A model transformation framework for CPAL
    Copyright (C) 2018 University of Luxembourg,
      National Research Council of Italy, and
      RealTime-at-Work

    Authors: Tingting Hu, Nicolas Navet,
      Ivan Cibrario Bertolotti,
      Loïc Fejoz, and Lionel Havet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

NHC -- A model transformation framework for CPAL
-------------

NHC is an automated tool that can be used to augment models written in
the CPAL Domain-Specific Language, with non-functional features such
as dependability. Model-to-model transformation is achieved by first
constructing an Abstract Syntax Tree corresponding to the initial
model and then manipulating the AST tree to add non-functional
features and last dump it back as CPAL source file. Currently, it
supports Linux and macOS.


Getting Started
---------------

The source tree of the automated MT framework is organized as
follows:

* mt_pressure_test.sh: the shell script runs the sample test program.

* Makefile

* main: it contains the top-layer program that starts the automated
  model transformation process.

* mt_samples:
  -- test.cpal: the sample user model
  -- demo.cpal: the temperature controller case study

* fault_tolerance: it contains the MT plugins for fault
  tolerance. Currently, only the plugin for NVP is included in this
  distribution.

  -- NVP_skeleton.cpal: the template used during the NVP
     transformation, which follows the pattern matching and expansion
     strategy.

* model_transform: it contains the utility functions performing basic
  types of transformation on a AST.

* dumper: it dumps an AST back into CPAL source code.

* utility: it contains all functions that are called during the parsing
  phase of a CPAL program and it builds the AST tree corresponding to
  invididual CPAL grammar elements.

* parser: the CPAL lexer and parser.

* include: header files for parser and utility

* README.txt

* LICENSE


Prerequisites
-------------

NHC requires that CPAL is already installed. It can be downloaded from
www.designcps.com/binaries.  It is recommended to download the
CPAL-Editor, namely the all-in-one package, to your ~/Document
directory for following use. NHC makes use of cpal2x in the CPAL
toolchain to beautify code according to indentation standard. And you
can also simulate and obtain the functional architecture view of the
transformed model with the CPAL-Editor.

Installation
----------

1. Download CPAL-Editor, add the path to CPAL binaries (they are under
the /tools directory) in your environmental variable:

PATH = path_to_cpal:$PATH
export PATH


Running the tests
-----------------
1. Download the NHC distribution an unzip if necessary.

2. Compile and build the whole source tree

   make clean
   make

3. Run NHC on the sample programs "test.cpal" and "demo.cpal" simply
   by

   ./mt_pressure_test.sh

   It applies NVP transformation based on the dependability annotation
   specified in "test.cpal" and "demo.cpal", using the
   "NVP_skeleton.cpal" as the template.  And it generates the
   NVP-enhanced model and outputs to "mt_test.cpal" and
   "mt_demo.cpal".

4. Start the CPAL-Editor

   cd CPAL-Editor/bin
   ./cpal-editor.sh

   Check the README.txt under CPAL-Editor for extra configuration
   instructions.

5. Create a workspace using the pull-down menu in the launched
   CPAL-Editor

6. Add test.cpal, mt_test.cpal, demo.cpal, mt_demo.cpal to the
   workspace using the pull-down menu under "File".

7. When you save the files, CPAL-Editor will automatically parse the
   models for you. CPAL-Editor offers two views: task view and
   architecture view. You can also start a simulation using the "Run"
   option.

8. Have fun! ;-)


Contacts
-------
Tingting Hu <tingting.hu@uni.lu>
Nicolas Navet <nicolas.navet@uni.lu>
Ivan Cibrario Bertolotti <ivan.cibrario@ieiit.cnr.it>
Loïc Fejoz <loic.fejoz@realtimeatwork.com>
Lionel Havet <lionel.havet@realtimeatwork.com>

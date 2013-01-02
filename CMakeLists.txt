project(org_commontk_xnat)

set(PLUGIN_export_directive "org_commontk_xnat_EXPORT")

include_directories(${QT_QTSCRIPT_INCLUDE_DIR})
include_directories(${qRestAPI_INCLUDE_DIRS})

set(PLUGIN_SRCS
  ctkActivator.cpp

  ctkXnatConnection.cpp
  ctkXnatConnectionFactory.cpp
  ctkXnatException.cpp
  ctkXnatExperiment.cpp
  ctkXnatObject.cpp
  ctkXnatProject.cpp
  ctkXnatReconstruction.cpp
  ctkXnatReconstructionFolder.cpp
  ctkXnatReconstructionResource.cpp
  ctkXnatReconstructionResourceFile.cpp
  ctkXnatScan.cpp
  ctkXnatScanFolder.cpp
  ctkXnatScanResource.cpp
  ctkXnatScanResourceFile.cpp
  ctkXnatServer.cpp
  ctkXnatSettings.cpp
  ctkXnatSubject.cpp
)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
  ctkActivator_p.h

  ctkXnatConnection.h
  ctkXnatExperiment.h
  ctkXnatObject.h
  ctkXnatProject.h
  ctkXnatReconstruction.h
  ctkXnatReconstructionFolder.h
  ctkXnatReconstructionResource.h
  ctkXnatReconstructionResourceFile.h
  ctkXnatScan.h
  ctkXnatScanFolder.h
  ctkXnatScanResource.h
  ctkXnatScanResourceFile.h
  ctkXnatServer.h
  ctkXnatSubject.h
)

# Qt Designer files which should be processed by Qts uic
set(PLUGIN_UI_FORMS
)

# QRC Files which should be compiled into the plugin
set(PLUGIN_resources
)

#Compute the plugin dependencies
ctkFunctionGetTargetLibraries(PLUGIN_target_libraries)

ctkMacroBuildPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  UI_FORMS ${PLUGIN_UI_FORMS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries} qRestAPI
#  TARGET_LIBRARIES ${PLUGIN_target_libraries}
)

# Testing
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

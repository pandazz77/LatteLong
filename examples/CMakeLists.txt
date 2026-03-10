
# EXAMPLE WINDOW ===========

add_executable(ExampleWindow example_window.cpp simple_dataset.hpp ProjComboBox.hpp)
target_link_libraries(ExampleWindow LatteLong)

# ==========================

# GEOJSON VIEWER ===========

add_executable(GeojsonViewer geojson_viewer.cpp ProjComboBox.hpp)
target_link_libraries(GeojsonViewer LatteLong)

# ==========================


# Features ===========

add_executable(FeaturesExample example_features.cpp simple_dataset.hpp)
target_link_libraries(FeaturesExample LatteLong)

# ==========================
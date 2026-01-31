
# EXAMPLE WINDOW ===========

add_executable(ExampleWindow example_window.cpp simple_dataset.hpp ProjComboBox.hpp)
target_link_libraries(ExampleWindow LatteLong)

# ==========================


add_executable(GeojsonViewer geojson_viewer.cpp ProjComboBox.hpp)
target_link_libraries(GeojsonViewer LatteLong)
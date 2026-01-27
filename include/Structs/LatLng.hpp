#pragma once

class LatLng{
    public:
        LatLng(double lat = 0, double lng = 0) : _lat(lat), _lng(lng) {}

        void setLat(double lat){
            _lat = lat;
        }

        void setLng(double lng){
            _lng = lng;
        }

        double lat() const {
            return _lat;
        }

        double lng() const {
            return _lng;
        }

    private:
        double _lat;
        double _lng;
};

inline LatLng LngLat(double lng = 0, double lat = 0){
    return LatLng(lat,lng);
}
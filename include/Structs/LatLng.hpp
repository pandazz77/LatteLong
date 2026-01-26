#pragma once

class LatLng{
    public:
        LatLng(double lat, double lng) : _lat(lat), _lng(lng) {}

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

inline LatLng LngLat(double lng, double lat){
    return LatLng(lat,lng);
}
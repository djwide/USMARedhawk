#ifndef STRUCTPROPS_H
#define STRUCTPROPS_H

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

*******************************************************************************************/

#include <ossie/CorbaUtils.h>
#include <CF/cf.h>
#include <ossie/PropertyMap.h>

struct accumMess_struct {
    accumMess_struct ()
    {
    };

    static std::string getId() {
        return std::string("accumMess");
    };

    unsigned char nodeID;
    float aveA;
    float wavelengthA;
    float locLongA;
    float locLatA;
    float compassA;
    float aoaA;
};

inline bool operator>>= (const CORBA::Any& a, accumMess_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("nodeID")) {
        if (!(props["nodeID"] >>= CORBA::Any::to_octet(s.nodeID))) return false;
    }
    if (props.contains("aveA")) {
        if (!(props["aveA"] >>= s.aveA)) return false;
    }
    if (props.contains("wavelengthA")) {
        if (!(props["wavelengthA"] >>= s.wavelengthA)) return false;
    }
    if (props.contains("locLongA")) {
        if (!(props["locLongA"] >>= s.locLongA)) return false;
    }
    if (props.contains("locLatA")) {
        if (!(props["locLatA"] >>= s.locLatA)) return false;
    }
    if (props.contains("compassA")) {
        if (!(props["compassA"] >>= s.compassA)) return false;
    }
    if (props.contains("aoaA")) {
        if (!(props["aoaA"] >>= s.aoaA)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const accumMess_struct& s) {
    redhawk::PropertyMap props;
 
    props["nodeID"] = CORBA::Any::from_octet(s.nodeID);
 
    props["aveA"] = s.aveA;
 
    props["wavelengthA"] = s.wavelengthA;
 
    props["locLongA"] = s.locLongA;
 
    props["locLatA"] = s.locLatA;
 
    props["compassA"] = s.compassA;
 
    props["aoaA"] = s.aoaA;
    a <<= props;
}

inline bool operator== (const accumMess_struct& s1, const accumMess_struct& s2) {
    if (s1.nodeID!=s2.nodeID)
        return false;
    if (s1.aveA!=s2.aveA)
        return false;
    if (s1.wavelengthA!=s2.wavelengthA)
        return false;
    if (s1.locLongA!=s2.locLongA)
        return false;
    if (s1.locLatA!=s2.locLatA)
        return false;
    if (s1.compassA!=s2.compassA)
        return false;
    if (s1.aoaA!=s2.aoaA)
        return false;
    return true;
}

inline bool operator!= (const accumMess_struct& s1, const accumMess_struct& s2) {
    return !(s1==s2);
}

struct Compass_struct {
    Compass_struct ()
    {
    };

    static std::string getId() {
        return std::string("Compass");
    };

    float compass;
    float aoa;
};

inline bool operator>>= (const CORBA::Any& a, Compass_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("compass")) {
        if (!(props["compass"] >>= s.compass)) return false;
    }
    if (props.contains("aoa")) {
        if (!(props["aoa"] >>= s.aoa)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const Compass_struct& s) {
    redhawk::PropertyMap props;
 
    props["compass"] = s.compass;
 
    props["aoa"] = s.aoa;
    a <<= props;
}

inline bool operator== (const Compass_struct& s1, const Compass_struct& s2) {
    if (s1.compass!=s2.compass)
        return false;
    if (s1.aoa!=s2.aoa)
        return false;
    return true;
}

inline bool operator!= (const Compass_struct& s1, const Compass_struct& s2) {
    return !(s1==s2);
}

struct runningAve_struct {
    runningAve_struct ()
    {
    };

    static std::string getId() {
        return std::string("runningAve");
    };

    float wavelength;
    float ave;
};

inline bool operator>>= (const CORBA::Any& a, runningAve_struct& s) {
    CF::Properties* temp;
    if (!(a >>= temp)) return false;
    const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
    if (props.contains("wavelength")) {
        if (!(props["wavelength"] >>= s.wavelength)) return false;
    }
    if (props.contains("ave")) {
        if (!(props["ave"] >>= s.ave)) return false;
    }
    return true;
}

inline void operator<<= (CORBA::Any& a, const runningAve_struct& s) {
    redhawk::PropertyMap props;
 
    props["wavelength"] = s.wavelength;
 
    props["ave"] = s.ave;
    a <<= props;
}

inline bool operator== (const runningAve_struct& s1, const runningAve_struct& s2) {
    if (s1.wavelength!=s2.wavelength)
        return false;
    if (s1.ave!=s2.ave)
        return false;
    return true;
}

inline bool operator!= (const runningAve_struct& s1, const runningAve_struct& s2) {
    return !(s1==s2);
}

#endif // STRUCTPROPS_H

#pragma once

#define FASTLED_RAND16_2053  ((uint16_t)(2053))
#define FASTLED_RAND16_13849 ((uint16_t)(13849))

#define APPLY_FASTLED_RAND16_2053(x) (x * FASTLED_RAND16_2053)

/// random number seed
uint16_t rand16seed;// = RAND16_SEED;

/// Generate an 8-bit random number
uint8_t random8()
{
    rand16seed = APPLY_FASTLED_RAND16_2053(rand16seed) + FASTLED_RAND16_13849;
    // return the sum of the high and low bytes, for better
    //  mixing and non-sequential correlation
    return (uint8_t)(((uint8_t)(rand16seed & 0xFF)) +
                     ((uint8_t)(rand16seed >> 8)));
}



uint8_t scale8( uint8_t i, uint8_t scale)
{
    return (((uint16_t)i) * (1+(uint16_t)(scale))) >> 8;
}
#define K255 255
#define K171 171
#define K170 170
#define K85  85

struct CHSV;
struct CRGB;

void hsv2rgb_rainbow( const CHSV& hsv, CRGB& rgb);


uint8_t scale8_video( uint8_t i, uint8_t scale) {
  return (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
}

uint8_t qadd8( uint8_t i, uint8_t j)
{
    unsigned int t = i + j;
    if( t > 255) t = 255;
    return t;
}

uint8_t sqrt16(uint16_t x)
{
    if( x <= 1) {
        return x;
    }

    uint8_t low = 1; // lower bound
    uint8_t hi, mid;

    if( x > 7904) {
        hi = 255;
    } else {
        hi = (x >> 5) + 8; // initial estimate for upper bound
    }

    do {
        mid = (low + hi) >> 1;
        if ((uint16_t)(mid * mid) > x) {
            hi = mid - 1;
        } else {
            if( mid == 255) {
                return 255;
            }
            low = mid + 1;
        }
    } while (hi >= low);

    return low - 1;
}

typedef enum {
    HUE_RED = 0,
    HUE_ORANGE = 32,
    HUE_YELLOW = 64,
    HUE_GREEN = 96,
    HUE_AQUA = 128,
    HUE_BLUE = 160,
    HUE_PURPLE = 192,
    HUE_PINK = 224
} HSVHue;

#define FIXFRAC8(N,D) (((N)*256)/(D))

uint8_t qsub8( uint8_t i, uint8_t j)
{
    int t = i - j;
    if( t < 0) t = 0;
    return t;
}



struct CHSV {
  uint8_t h;
  uint8_t s;
  uint8_t v;

  CHSV(uint8_t h, uint8_t s, uint8_t v) {
    this->h = h;
    this->s = s;
    this->v = v;
  };

  CHSV(CHSV* src) {
    this->h = src->h;
    this->s = src->s;
    this->v = src->v;
  }

  CHSV() {
    this->h = 0;
    this->s = 0;
    this->v = 0;
  }
};

struct CRGB {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  CRGB(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
  };

  CRGB(CRGB* src) {
    this->r = src->r;
    this->g = src->g;
    this->b = src->b;
  }

  CRGB() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
  }

  CRGB(const CHSV& rhs)
  {
     hsv2rgb_rainbow( rhs, *this);
  }

   CRGB& operator= (const CHSV& rhs)
    {
        hsv2rgb_rainbow( rhs, *this);
        return *this;
    }

    inline operator bool() const
    {
        return r || g || b;
    }
};


bool operator== (const CRGB& lhs, const CRGB& rhs)
{
    return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b);
}

bool operator!= (const CRGB& lhs, const CRGB& rhs)
{
    return !(lhs == rhs);
}

bool operator< (const CRGB& lhs, const CRGB& rhs)
{
    uint16_t sl, sr;
    sl = lhs.r + lhs.g + lhs.b;
    sr = rhs.r + rhs.g + rhs.b;
    return sl < sr;
}

bool operator> (const CRGB& lhs, const CRGB& rhs)
{
    uint16_t sl, sr;
    sl = lhs.r + lhs.g + lhs.b;
    sr = rhs.r + rhs.g + rhs.b;
    return sl > sr;
}

bool operator>= (const CRGB& lhs, const CRGB& rhs)
{
    uint16_t sl, sr;
    sl = lhs.r + lhs.g + lhs.b;
    sr = rhs.r + rhs.g + rhs.b;
    return sl >= sr;
}

bool operator<= (const CRGB& lhs, const CRGB& rhs)
{
    uint16_t sl, sr;
    sl = lhs.r + lhs.g + lhs.b;
    sr = rhs.r + rhs.g + rhs.b;
    return sl <= sr;
}

CHSV rgb2hsv_approximate( const CRGB& rgb)
{
    uint8_t r = rgb.r;
    uint8_t g = rgb.g;
    uint8_t b = rgb.b;
    uint8_t h, s, v;
    
    // find desaturation
    uint8_t desat = 255;
    if( r < desat) desat = r;
    if( g < desat) desat = g;
    if( b < desat) desat = b;
    
    // remove saturation from all channels
    r -= desat;
    g -= desat;
    b -= desat;
    
    //Serial.print("desat="); Serial.print(desat); Serial.println("");
    
    //uint8_t orig_desat = sqrt16( desat * 256);
    //Serial.print("orig_desat="); Serial.print(orig_desat); Serial.println("");
    
    // saturation is opposite of desaturation
    s = 255 - desat;
    //Serial.print("s.1="); Serial.print(s); Serial.println("");
    
    if( s != 255 ) {
        // undo 'dimming' of saturation
        s = 255 - sqrt16( (255-s) * 256);
    }
    // without lib8tion: float ... ew ... sqrt... double ew, or rather, ew ^ 0.5
    // if( s != 255 ) s = (255 - (256.0 * sqrt( (float)(255-s) / 256.0)));
    //Serial.print("s.2="); Serial.print(s); Serial.println("");
    
    
    // at least one channel is now zero
    // if all three channels are zero, we had a
    // shade of gray.
    if( (r + g + b) == 0) {
        // we pick hue zero for no special reason
        return CHSV( 0, 0, 255 - s);
    }
    
    // scale all channels up to compensate for desaturation
    if( s < 255) {
        if( s == 0) s = 1;
        uint32_t scaleup = 65535 / (s);
        r = ((uint32_t)(r) * scaleup) / 256;
        g = ((uint32_t)(g) * scaleup) / 256;
        b = ((uint32_t)(b) * scaleup) / 256;
    }
    //Serial.print("r.2="); Serial.print(r); Serial.println("");
    //Serial.print("g.2="); Serial.print(g); Serial.println("");
    //Serial.print("b.2="); Serial.print(b); Serial.println("");
    
    uint16_t total = r + g + b;
    
    //Serial.print("total="); Serial.print(total); Serial.println("");
    
    // scale all channels up to compensate for low values
    if( total < 255) {
        if( total == 0) total = 1;
        uint32_t scaleup = 65535 / (total);
        r = ((uint32_t)(r) * scaleup) / 256;
        g = ((uint32_t)(g) * scaleup) / 256;
        b = ((uint32_t)(b) * scaleup) / 256;
    }
    //Serial.print("r.3="); Serial.print(r); Serial.println("");
    //Serial.print("g.3="); Serial.print(g); Serial.println("");
    //Serial.print("b.3="); Serial.print(b); Serial.println("");
    
    if( total > 255 ) {
        v = 255;
    } else {
        v = qadd8(desat,total);
        // undo 'dimming' of brightness
        if( v != 255) v = sqrt16( v * 256);
        // without lib8tion: float ... ew ... sqrt... double ew, or rather, ew ^ 0.5
        // if( v != 255) v = (256.0 * sqrt( (float)(v) / 256.0));
        
    }
    
    //Serial.print("v="); Serial.print(v); Serial.println("");
    

    
    //Serial.print("s.3="); Serial.print(s); Serial.println("");
    
    
    // since this wasn't a pure shade of gray,
    // the interesting question is what hue is it
    
    
    
    // start with which channel is highest
    // (ties don't matter)
    uint8_t highest = r;
    if( g > highest) highest = g;
    if( b > highest) highest = b;
    
    if( highest == r ) {
        // Red is highest.
        // Hue could be Purple/Pink-Red,Red-Orange,Orange-Yellow
        if( g == 0 ) {
            // if green is zero, we're in Purple/Pink-Red
            h = (HUE_PURPLE + HUE_PINK) / 2;
            h += scale8( qsub8(r, 128), FIXFRAC8(48,128));
        } else if ( (r - g) > g) {
            // if R-G > G then we're in Red-Orange
            h = HUE_RED;
            h += scale8( g, FIXFRAC8(32,85));
        } else {
            // R-G < G, we're in Orange-Yellow
            h = HUE_ORANGE;
            h += scale8( qsub8((g - 85) + (171 - r), 4), FIXFRAC8(32,85)); //221
        }
        
    } else if ( highest == g) {
        // Green is highest
        // Hue could be Yellow-Green, Green-Aqua
        if( b == 0) {
            // if Blue is zero, we're in Yellow-Green
            //   G = 171..255
            //   R = 171..  0
            h = HUE_YELLOW;
            uint8_t radj = scale8( qsub8(171,r),   47); //171..0 -> 0..171 -> 0..31
            uint8_t gadj = scale8( qsub8(g,171),   96); //171..255 -> 0..84 -> 0..31;
            uint8_t rgadj = radj + gadj;
            uint8_t hueadv = rgadj / 2;
            h += hueadv;
            //h += scale8( qadd8( 4, qadd8((g - 128), (128 - r))),
            //             FIXFRAC8(32,255)); //
        } else {
            // if Blue is nonzero we're in Green-Aqua
            if( (g-b) > b) {
                h = HUE_GREEN;
                h += scale8( b, FIXFRAC8(32,85));
            } else {
                h = HUE_AQUA;
                h += scale8( qsub8(b, 85), FIXFRAC8(8,42));
            }
        }
        
    } else /* highest == b */ {
        // Blue is highest
        // Hue could be Aqua/Blue-Blue, Blue-Purple, Purple-Pink
        if( r == 0) {
            // if red is zero, we're in Aqua/Blue-Blue
            h = HUE_AQUA + ((HUE_BLUE - HUE_AQUA) / 4);
            h += scale8( qsub8(b, 128), FIXFRAC8(24,128));
        } else if ( (b-r) > r) {
            // B-R > R, we're in Blue-Purple
            h = HUE_BLUE;
            h += scale8( r, FIXFRAC8(32,85));
        } else {
            // B-R < R, we're in Purple-Pink
            h = HUE_PURPLE;
            h += scale8( qsub8(r, 85), FIXFRAC8(32,85));
        }
    }
    
    h += 1;
    return CHSV( h, s, v);
}

uint8_t applyGamma_video( uint8_t brightness, float gamma)
{
    float orig;
    float adj;
    orig = (float)(brightness) / (255.0);
    adj =  pow( orig, gamma)   * (255.0);
    uint8_t result = (uint8_t)(adj);
    if( (brightness > 0) && (result == 0)) {
        result = 1; // never gamma-adjust a positive number down to zero
    }
    return result;
}

CRGB applyGamma_video( const CRGB& orig, float gamma)
{
    CRGB adj;
    adj.r = applyGamma_video( orig.r, gamma);
    adj.g = applyGamma_video( orig.g, gamma);
    adj.b = applyGamma_video( orig.b, gamma);
    return adj;
}


void hsv2rgb_rainbow( const CHSV& hsv, CRGB& rgb)
{
    // Yellow has a higher inherent brightness than
    // any other color; 'pure' yellow is perceived to
    // be 93% as bright as white.  In order to make
    // yellow appear the correct relative brightness,
    // it has to be rendered brighter than all other
    // colors.
    // Level Y1 is a moderate boost, the default.
    // Level Y2 is a strong boost.
    const uint8_t Y1 = 1;
    const uint8_t Y2 = 0;
    
    // G2: Whether to divide all greens by two.
    // Depends GREATLY on your particular LEDs
    const uint8_t G2 = 0;
    
    // Gscale: what to scale green down by.
    // Depends GREATLY on your particular LEDs
    const uint8_t Gscale = 0;
    
    
    uint8_t hue = hsv.h;
    uint8_t sat = hsv.s;
    uint8_t val = hsv.v;
    
    uint8_t offset = hue & 0x1F; // 0..31
    
    // offset8 = offset * 8
    uint8_t offset8 = offset;
    {
#if defined(__AVR__)
        // Left to its own devices, gcc turns "x <<= 3" into a loop
        // It's much faster and smaller to just do three single-bit shifts
        // So this business is to force that.
        offset8 <<= 1;
        asm volatile("");
        offset8 <<= 1;
        asm volatile("");
        offset8 <<= 1;
#else
        // On ARM and other non-AVR platforms, we just shift 3.
        offset8 <<= 3;
#endif
    }
    
    uint8_t third = scale8( offset8, (256 / 3)); // max = 85
    
    uint8_t r, g, b;
    
    if( ! (hue & 0x80) ) {
        // 0XX
        if( ! (hue & 0x40) ) {
            // 00X
            //section 0-1
            if( ! (hue & 0x20) ) {
                // 000
                //case 0: // R -> O
                r = K255 - third;
                g = third;
                b = 0;
            } else {
                // 001
                //case 1: // O -> Y
                if( Y1 ) {
                    r = K171;
                    g = K85 + third ;
                    b = 0;
                }
                if( Y2 ) {
                    r = K170 + third;
                    //uint8_t twothirds = (third << 1);
                    uint8_t twothirds = scale8( offset8, ((256 * 2) / 3)); // max=170
                    g = K85 + twothirds;
                    b = 0;
                }
            }
        } else {
            //01X
            // section 2-3
            if( !  (hue & 0x20) ) {
                // 010
                //case 2: // Y -> G
                if( Y1 ) {
                    //uint8_t twothirds = (third << 1);
                    uint8_t twothirds = scale8( offset8, ((256 * 2) / 3)); // max=170
                    r = K171 - twothirds;
                    g = K170 + third;
                    b = 0;
                }
                if( Y2 ) {
                    r = K255 - offset8;
                    g = K255;
                    b = 0;
                }
            } else {
                // 011
                // case 3: // G -> A
                r = 0;
                g = K255 - third;
                b = third;
            }
        }
    } else {
        // section 4-7
        // 1XX
        if( ! (hue & 0x40) ) {
            // 10X
            if( ! ( hue & 0x20) ) {
                // 100
                //case 4: // A -> B
                r = 0;
                //uint8_t twothirds = (third << 1);
                uint8_t twothirds = scale8( offset8, ((256 * 2) / 3)); // max=170
                g = K171 - twothirds; //K170?
                b = K85  + twothirds;
                
            } else {
                // 101
                //case 5: // B -> P
                r = third;
                g = 0;
                b = K255 - third;
                
            }
        } else {
            if( !  (hue & 0x20)  ) {
                // 110
                //case 6: // P -- K
                r = K85 + third;
                g = 0;
                b = K171 - third;
                
            } else {
                // 111
                //case 7: // K -> R
                r = K170 + third;
                g = 0;
                b = K85 - third;
                
            }
        }
    }
    
    // This is one of the good places to scale the green down,
    // although the client can scale green down as well.
    if( G2 ) g = g >> 1;
    if( Gscale ) g = scale8_video( g, Gscale);
    
    // Scale down colors if we're desaturated at all
    // and add the brightness_floor to r, g, and b.
    if( sat != 255 ) {
        if( sat == 0) {
            r = 255; b = 255; g = 255;
        } else {
            //nscale8x3_video( r, g, b, sat);
            if( r ) r = scale8( r, sat);
            if( g ) g = scale8( g, sat);
            if( b ) b = scale8( b, sat);
            
            uint8_t desat = 255 - sat;
            desat = scale8( desat, desat);
            
            uint8_t brightness_floor = desat;
            r += brightness_floor;
            g += brightness_floor;
            b += brightness_floor;
        }
    }
    
    // Now scale everything down if we're at value < 255.
    if( val != 255 ) {
        
        val = scale8_video( val, val);
        if( val == 0 ) {
            r=0; g=0; b=0;
        } else {
            // nscale8x3_video( r, g, b, val);
            if( r ) r = scale8( r, val);
            if( g ) g = scale8( g, val);
            if( b ) b = scale8( b, val);
        }
    }
    
    // Here we have the old AVR "missing std X+n" problem again
    // It turns out that fixing it winds up costing more than
    // not fixing it.
    // To paraphrase Dr Bronner, profile! profile! profile!
    //asm volatile(  ""  :  :  : "r26", "r27" );
    //asm volatile (" movw r30, r26 \n" : : : "r30", "r31");
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
}

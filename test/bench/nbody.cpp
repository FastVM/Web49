#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

static constexpr const double PI = 3.141592653589793;
static constexpr const double SOLAR_MASS = 4 * PI * PI;
static constexpr const double DAYS_PER_YEAR = 365.24;

class Body {
public:
  double x, vx, y, vy, z, vz;
  double mass;

  Body &offsetMomentum(const double px, const double py,
                       const double pz) noexcept {
    vx = -px / SOLAR_MASS;
    vy = -py / SOLAR_MASS;
    vz = -pz / SOLAR_MASS;
    return *this;
  }
};

constexpr Body jupiter() {
  return Body{/*x =*/4.84143144246472090e+00,
              /*vx =*/1.66007664274403694e-03 * DAYS_PER_YEAR,
              /*y =*/-1.16032004402742839e+00,
              /*vy =*/7.69901118419740425e-03 * DAYS_PER_YEAR,
              /*z =*/-1.03622044471123109e-01,
              /*vz =*/-6.90460016972063023e-05 * DAYS_PER_YEAR,
              /*mass =*/9.54791938424326609e-04 * SOLAR_MASS};
}

constexpr Body saturn() {
  return Body{/*x = */ 8.34336671824457987e+00,
              /*vx = */ -2.76742510726862411e-03 * DAYS_PER_YEAR,
              /*y = */ 4.12479856412430479e+00,
              /*vy = */ 4.99852801234917238e-03 * DAYS_PER_YEAR,
              /*z = */ -4.03523417114321381e-01,
              /*vz = */ 2.30417297573763929e-05 * DAYS_PER_YEAR,
              /*mass =*/2.85885980666130812e-04 * SOLAR_MASS};
}

constexpr Body uranus() {
  return Body{/*x =*/1.28943695621391310e+01,
              /*vx = */ 2.96460137564761618e-03 * DAYS_PER_YEAR,
              /*y =*/-1.51111514016986312e+01,
              /*vy = */ 2.37847173959480950e-03 * DAYS_PER_YEAR,
              /*z =*/-2.23307578892655734e-01,
              /*vz = */ -2.96589568540237556e-05 * DAYS_PER_YEAR,
              /*mass =*/4.36624404335156298e-05 * SOLAR_MASS};
}

constexpr Body neptune() {
  return Body{/*x = */ 1.53796971148509165e+01,
              /*vx = */ 2.68067772490389322e-03 * DAYS_PER_YEAR,
              /*y = */ -2.59193146099879641e+01,
              /*vy = */ 1.62824170038242295e-03 * DAYS_PER_YEAR,
              /*z = */ 1.79258772950371181e-01,
              /*vz = */ -9.51592254519715870e-05 * DAYS_PER_YEAR,
              /*mass = */ 5.15138902046611451e-05 * SOLAR_MASS};
}

constexpr Body sun() {
  return Body{/*x = */ 0,
              /*vx = */ 0,
              /*y = */ 0,
              /*vy = */ 0,
              /*z = */ 0,
              /*vz = */ 0,
              /*mass = */ SOLAR_MASS};
}

class NBodySystem {
private:
  std::array<Body, 5> bodies;
  static constexpr unsigned int bodies_size = 5;

public:
  NBodySystem() noexcept
      : bodies{{sun(), jupiter(), saturn(), uranus(), neptune()}} {
    double px = 0.0;
    double py = 0.0;
    double pz = 0.0;
    for (unsigned i = 0; i != bodies_size; ++i) {
      px += bodies[i].vx * bodies[i].mass;
      py += bodies[i].vy * bodies[i].mass;
      pz += bodies[i].vz * bodies[i].mass;
    }
    bodies[0].offsetMomentum(px, py, pz);
  }

  void advance(const double dt) noexcept {
    constexpr const unsigned N = ((bodies_size - 1) * bodies_size) / 2;
    static double Rdx[N], Rdy[N], Rdz[N];
    static double mag[N];

    for (unsigned int i = 0, k = 0; i != bodies_size - 1; ++i) {
      for (unsigned int j = i + 1; j != bodies_size; ++j, ++k) {
        Rdx[k] = bodies[i].x - bodies[j].x;
        Rdy[k] = bodies[i].y - bodies[j].y;
        Rdz[k] = bodies[i].z - bodies[j].z;
      }
    }

    for (unsigned int i = 0; i != N; ++i) {
      const double dx = Rdx[i];
      const double dy = Rdy[i];
      const double dz = Rdz[i];
      const double dSquared = dx*dx + dy*dy + dz*dz;
      double distance = sqrt(dSquared);
      const double dmag = dt / (dSquared * distance);
      mag[i] = dmag;
    }

    for (unsigned int i = 0, k = 0; i != bodies_size - 1; ++i) {
      Body &iBody = bodies[i];
      for (unsigned int j = i + 1; j != bodies_size; ++j, ++k) {
        Body &jBody = bodies[j];
        double const jmm = jBody.mass * mag[k];
        iBody.vx -= Rdx[k] * jmm;
        iBody.vy -= Rdy[k] * jmm;
        iBody.vz -= Rdz[k] * jmm;

        double const imm = iBody.mass * mag[k];
        jBody.vx += Rdx[k] * imm;
        jBody.vy += Rdy[k] * imm;
        jBody.vz += Rdz[k] * imm;
      }
    }

    for (unsigned int i = 0; i != bodies_size; ++i) {
      Body &iBody = bodies[i];
      iBody.x += dt * iBody.vx;
      iBody.y += dt * iBody.vy;
      iBody.z += dt * iBody.vz;
    }
  }

  double energy() noexcept {
    double e = 0.0;

    for (unsigned int i = 0; i != bodies_size; ++i) {
      Body const iBody = bodies[i];
      e += 0.5 * iBody.mass *
           (iBody.vx * iBody.vx + iBody.vy * iBody.vy + iBody.vz * iBody.vz);

      for (unsigned int j = i + 1; j != bodies_size; ++j) {
        Body const &jBody = bodies[j];

        const double dx = iBody.x - jBody.x;
        const double dy = iBody.y - jBody.y;
        const double dz = iBody.z - jBody.z;

        const double distance = sqrt(dx * dx + dy * dy + dz * dz);
        e -= (iBody.mass * jBody.mass) / distance;
      }
    }
    return e;
  }
};

int main(int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);
  int n = std::atoi(argv[1]);

  NBodySystem bodies;
  std::cout << std::setprecision(9) << bodies.energy() << std::endl;
  for (int i = 0; i < n; ++i)
    bodies.advance(0.01);
  std::cout << bodies.energy() << '\n';
}

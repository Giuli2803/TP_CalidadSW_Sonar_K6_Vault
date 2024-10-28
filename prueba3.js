import http from 'k6/http';
import { check, sleep } from 'k6';

export const options = {
  stages: [
    { duration: '10s', target: 5 },
    { duration: '20s', target: 30 },
    { duration: '10s', target: 8 },
  ],
};

export default function () {
  const res = http.get('http://test.k6.io');
  check(res, { 'status was 200': (r) => r.status == 200 });
  sleep(1); // Esta linea especifica el tiempo de espera entre cada peticion
}

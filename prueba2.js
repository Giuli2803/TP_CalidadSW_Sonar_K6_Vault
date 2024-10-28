import http from 'k6/http';
import { sleep } from 'k6';
export const options = {
  vus: 20,
  duration: '15s',
};
export default function () {
  http.get('http://test.k6.io');
  sleep(5); // Esta linea especifica el tiempo de espera entre cada peticion
}

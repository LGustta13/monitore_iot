import { useRoutes } from 'react-router-dom';

import { Dashboard } from '../pages/Dashboard';
import { Home } from '../pages/Home';

export function Routes() {

    const home = {
        path: '/',
        element: <Home />
    };

    const dashboard = {
        path: '/dashboard',
        element: <Dashboard />,
    }

    const routing = useRoutes([home, dashboard]);

    return <>{routing}</>;
}
import { ReactNode, createContext, useContext, useState } from "react";

type RoutesContextProviderProps = {
    children: ReactNode,
}

type RoutesContextDataProps = {
    route: string,
    setRoute:(route: RouteProps) => void
}

type RouteProps = "/Home" | "/Dash";

const RoutesContext = createContext<RoutesContextDataProps>({} as RoutesContextDataProps);

export function RoutesContextProvider({ children }: RoutesContextProviderProps) {

    const [route, setRoute] = useState<"/Home" | "/Dash">("/Home");

    return (
        <RoutesContext.Provider value={{route, setRoute}}>
            {children}
        </RoutesContext.Provider>
    )
}

export function useRoutes() {
    const context = useContext(RoutesContext);
    return context;
}

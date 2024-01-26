import { ReactNode, createContext, useContext, useState } from "react";

type SupplyProps = {
    id: number,
    tank: string,
    date: Date,
    amount: number,
    attendant: string,
    plate: string,
    driver: string,
}

type SearchContextProviderProps = {
    children: ReactNode;
}

type SearchContextDataProps = {
    handleSearchDataByDate: (initial: Date | null, final: Date | null) => void,
    supplies: SupplyProps[]
}

const SearchContext = createContext<SearchContextDataProps>({} as SearchContextDataProps);

export function SearchContextProvider({ children }: SearchContextProviderProps) {

    const [supplies, setSupplies] = useState<SupplyProps[]>([])

    async function handleSearchDataByDate(initial: Date | null, final: Date | null) {
        let response = null;
        const initialDate = initial?.toString();
        const finalDate = final?.toString();

        if(!initial || !final) {
            response = await fetch(`http://localhost:5173/api/supplies`)
            
        } else {
            response = await fetch(`http://localhost:5173/api/supplies/${initialDate}/${finalDate}`)
        }
        
        const data = await response.json()
        setSupplies(data)
    }

    return (
        <SearchContext.Provider value={{ handleSearchDataByDate, supplies }}>
            {children}
        </SearchContext.Provider>
    )
}

export function useSearchSupplies() {
    const context = useContext(SearchContext);
    return context;
}







/**
 * 
 * Buscar uma data entre duas outras
 * 
var dateFrom = "02/05/2013";
var dateTo = "02/09/2013";
var dateCheck = "02/07/2013";

var d1 = dateFrom.split("/");
var d2 = dateTo.split("/");
var c = dateCheck.split("/");

var from = new Date(d1[2], parseInt(d1[1])-1, d1[0]);  // -1 because months are from 0 to 11
var to   = new Date(d2[2], parseInt(d2[1])-1, d2[0]);
var check = new Date(c[2], parseInt(c[1])-1, c[0]);

console.log(check > from && check < to)
 */
import './styles.css'
import Header from '../../components/Header'
import { useState } from 'react'
import Listagem from '../Listagem'
import { useRoutes } from '../../hooks/useRoutes';


import Dash from '../Dashboard';


export default function Home() {

  const [activeSideBar, setActiveSideBar] = useState(true);
  const { route } = useRoutes();


  function handleActiveSideBar() {
    setActiveSideBar(!activeSideBar)
  }

  return (
    <>
      <Header onActiveSideBar={handleActiveSideBar} activeSideBar={activeSideBar} />

      {
        route === "/Home" ? (<Listagem />) : (
          route === "/Dash" ? (<Dash />) : (<></>)
        )
      }
    </>
  )
}
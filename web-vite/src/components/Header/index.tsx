import './styles.css'
import User from '../User'
import SideBar from '../SideBar'
import { List } from '@phosphor-icons/react'

type HeaderProps = {
  onSearchData: (initialDate: string, finalDate: string) => void
  onActiveSideBar: () => void;
  activeSideBar: boolean;
}

export default function Header({ onSearchData, onActiveSideBar, activeSideBar }: HeaderProps) {

  return (
    <header>
      <List className='header-icon' onClick={onActiveSideBar} />
      <h1>Bem-vindo</h1>

      <User />
      <SideBar active={activeSideBar} onSearchData={onSearchData} />
    </header>
  )
}
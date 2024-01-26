import './styles.css'
import User from '../User'
import SideBar from '../SideBar'
import { List } from '@phosphor-icons/react'

type HeaderProps = {
  onActiveSideBar: () => void;
  activeSideBar: boolean;
}

export default function Header({ onActiveSideBar, activeSideBar }: HeaderProps) {

  return (
    <header>
      <List className='header-icon' onClick={onActiveSideBar} />
      <h1>Bem-vindo</h1>

      <User />
      <SideBar active={activeSideBar} />
    </header>
  )
}